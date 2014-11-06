{
    volScalarField& he = thermo.he();

    Urel == U;
    fvOptions.makeRelative(Urel);
    phirel == phi;
    fvOptions.makeRelative(phirel);

    fvScalarMatrix EEqn
    (
        fvm::div(phirel, he)
      + (
            he.name() == "e"
          ? fvc::div(phirel, volScalarField("Ekp", 0.5*(magSqr(Urel) - magSqr(U-Urel))+ p/rho))
          : fvc::div(phirel, volScalarField("K", 0.5*(magSqr(Urel) - magSqr(U-Urel))))
        )
      - fvm::laplacian(turbulence->alphaEff(), he)
     ==
        fvOptions(rho, he)
        // Viscous heating: note sign (devRhoReff has a minus in it)
      - (turbulence->devRhoReff() && fvc::grad(Urel))
    );

    EEqn.relax();

    fvOptions.constrain(EEqn);

    EEqn.solve();

    fvOptions.correct(he);

    thermo.correct();
}
