// addapted energy equation, includes dissipation, inspired from:
// http://www.cfd-online.com/Forums/openfoam/76349-rhosimplefoam-loss-total-enthalpy.html
{
    volScalarField& he = thermo.he();

    fvScalarMatrix EEqn
    (
        fvm::div(phi,he)
        // adds diffusive transport, does also take the turbulent diffusive
        // transport into account
        - fvm::laplacian(turbulence->alphaEff(), he)
    );
    // add reversible work as implicite source term
    if (he.name() == "e"){
        EEqn += p*fvc::div(fvc::absolute(phi/fvc::interpolate(rho),U));
    }else{
        fvOptions.makeRelative(U);
        EEqn -= fvc::grad(p)&U;
        fvOptions.makeAbsolute(U);
    }
    // add viscous dissipation/heating
    if (runTime.controlDict().found("dissipation"))
    {
        tmp<volTensorField> tgradU = fvc::grad(U); 
        // read parameter dissipation from control
        // dict which scales the dissipation term 
        float dissipation_scale = readScalar(
                runTime.controlDict().lookup("dissipation"));
        // add it to the energy equation
        if (dissipation_scale > 0){
            Info << "dissipation scaling is: " << dissipation_scale << endl;
            EEqn -= dissipation_scale*(turbulence->muEff()*dev(twoSymm(tgradU()))-(2.0/3.0)*rho*turbulence->k()*I)&&tgradU();
        }
    }

    EEqn += fvOptions(rho, he);

    EEqn.relax();

    fvOptions.constrain(EEqn);

    EEqn.solve();

    fvOptions.correct(he);

    thermo.correct();
}
