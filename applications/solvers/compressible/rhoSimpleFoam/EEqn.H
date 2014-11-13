{
    volScalarField& he = thermo.he();

    Urel == U;
    fvOptions.makeRelative(Urel);
    Uframe = U - Urel;
    phirel == phi;
    fvOptions.makeRelative(phirel);

    fvScalarMatrix EEqn
    (
        fvm::div(phirel, he)
      + (
            he.name() == "e"
          ? fvc::div(phirel, volScalarField("Ekp", 0.5*magSqr(Urel) + p/rho))
          : fvc::div(phirel, volScalarField("K", 0.5*magSqr(Urel)))
        )
        - fvm::laplacian(turbulence->alphaEff(), he)
     ==
        fvOptions(rho, he)
        // Viscous heating: note sign (devRhoReff has a minus in it)
        //- (turbulence->devRhoReff() && fvc::grad(Urel))
    );

    EEqn.relax();

    fvOptions.constrain(EEqn);

    EEqn.solve();

    volScalarField Cp = thermo.Cp();
    Info<< "T before bounding  max/min : "
        << max(he/Cp).value() << " "
        << min(he/Cp).value() << endl;
    if (he.name() == "h"){
        he = Foam::min(he, TMax*Cp);
        he = Foam::max(he, TMin*Cp);
    }else{
        he = Foam::min(he+p/rho, TMax*Cp)-p/rho;
        he = Foam::max(he+p/rho, TMin*Cp)-p/rho;
    }
    he.correctBoundaryConditions();

    fvOptions.correct(he);

    thermo.correct();

    Info<< "T final max/min : "
        << max(he/Cp).value() << " "
        << min(he/Cp).value() << endl;
}
