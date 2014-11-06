{
    volScalarField& he = thermo.he();
    volVectorField Urel
        (
            IOobject
            (
                "Urel",
                runTime.timeName(),
                mesh,
                IOobject::NO_READ,
                IOobject::NO_WRITE
            ),
            U
        );
    fvOptions.makeRelative(Urel);
    surfaceScalarField phirel
        (
            IOobject
            (
                "phirel",
                runTime.timeName(),
                mesh,
                IOobject::NO_READ,
                IOobject::NO_WRITE
            ),
            phi
        );
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
    );

    EEqn.relax();

    fvOptions.constrain(EEqn);

    EEqn.solve();

    fvOptions.correct(he);

    thermo.correct();


}
