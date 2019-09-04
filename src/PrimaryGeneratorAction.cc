//
// ********************************************************************
// * License and Disclaimer                                           *
// *                                                                  *
// * The  Geant4 software  is  copyright of the Copyright Holders  of *
// * the Geant4 Collaboration.  It is provided  under  the terms  and *
// * conditions of the Geant4 Software License,  included in the file *
// * LICENSE and available at  http://cern.ch/geant4/license .  These *
// * include a list of copyright holders.                             *
// *                                                                  *
// * Neither the authors of this software system, nor their employing *
// * institutes,nor the agencies providing financial support for this *
// * work  make  any representation or  warranty, express or implied, *
// * regarding  this  software system or assume any liability for its *
// * use.  Please see the license in the file  LICENSE  and URL above *
// * for the full disclaimer and the limitation of liability.         *
// *                                                                  *
// * This  code  implementation is the result of  the  scientific and *
// * technical work of the GEANT4 collaboration.                      *
// * By using,  copying,  modifying or  distributing the software (or *
// * any work based  on the software)  you  agree  to acknowledge its *
// * use  in  resulting  scientific  publications,  and indicate your *
// * acceptance of all terms of the Geant4 Software license.          *
// ********************************************************************
//
/// \file PrimaryGeneratorAction.cc
/// \brief Implementation of the PrimaryGeneratorAction class
//
// $Id$
// 
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
#include "PrimaryGeneratorAction.hh"

#include "G4Event.hh"
#include "G4ParticleTable.hh"
#include "G4IonTable.hh"
#include "G4ParticleDefinition.hh"
#include "G4Geantino.hh"
#include "G4SystemOfUnits.hh"
#include "Randomize.hh"

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

PrimaryGeneratorAction::PrimaryGeneratorAction()
 : G4VUserPrimaryGeneratorAction()
 //  fParticleGun(0)

{

 G4int n_particle = 1;
  
	fParticleGun  = new G4ParticleGun(n_particle);
}





//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

PrimaryGeneratorAction::~PrimaryGeneratorAction()
{
  delete fParticleGun;
}




//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void PrimaryGeneratorAction::GeneratePrimaries(G4Event* anEvent)
{


  fParticleGun->SetParticleEnergy(0*eV);



        G4int seed = rand()%100;
        G4int seed2 = rand()%100;
        G4int seed3 = rand()%100;

	if (seed<98)
	{
		fParticleGun->SetParticlePosition(G4ThreeVector(0.*mm,0.*mm,0.*mm));
		fParticleGun->SetParticleMomentumDirection(G4ThreeVector(0.,0.,1.));          

			G4int Z = 27, A = 60;
			G4double ionCharge   = 0.*eplus;
			G4double excitEnergy = 0.*keV;

			G4ParticleDefinition* ion
				= G4IonTable::GetIonTable()->GetIon(Z,A,excitEnergy);
			fParticleGun->SetParticleDefinition(ion);
			fParticleGun->SetParticleCharge(ionCharge);
	
			fParticleGun->GeneratePrimaryVertex(anEvent);
	}
	if (seed<98)
        {
                fParticleGun->SetParticlePosition(G4ThreeVector(0.*mm,0.*mm,0.*mm));
                fParticleGun->SetParticleMomentumDirection(G4ThreeVector(0.,0.,1.));

                        G4int Z = 55, A =137;
                        G4double ionCharge   = 0.*eplus;
                        G4double excitEnergy = 0.*keV;

                        G4ParticleDefinition* ion
                                = G4IonTable::GetIonTable()->GetIon(Z,A,excitEnergy);
                        fParticleGun->SetParticleDefinition(ion);
                        fParticleGun->SetParticleCharge(ionCharge);

                        fParticleGun->GeneratePrimaryVertex(anEvent);
        }  
	if (seed<98)
        {
                fParticleGun->SetParticlePosition(G4ThreeVector(0.*mm,0.*mm,0.*mm));
                fParticleGun->SetParticleMomentumDirection(G4ThreeVector(0.,0.,1.));

                        G4int Z = 56, A = 133;
                        G4double ionCharge   = 0.*eplus;
                        G4double excitEnergy = 0.*keV;

                        G4ParticleDefinition* ion
                                = G4IonTable::GetIonTable()->GetIon(Z,A,excitEnergy);
                        fParticleGun->SetParticleDefinition(ion);
                        fParticleGun->SetParticleCharge(ionCharge);

                        fParticleGun->GeneratePrimaryVertex(anEvent);
        }
	if( seed2<1)
	{
		G4double theta = 2*CLHEP::pi*G4UniformRand();
                G4double radii = 19.05*G4UniformRand();
                G4double height = 38.1*G4UniformRand();  
			fParticleGun->SetParticlePosition(G4ThreeVector(radii*std::cos(theta)*mm,radii*std::sin(theta)*mm,(height-59.6)*mm));

			fParticleGun->SetParticleMomentumDirection(G4ThreeVector(1.,0.,0.));          

                	        G4int Z = 57, A = 138;
			G4double ionCharge   = 0.*eplus;
                        G4double excitEnergy = 0.*keV;
	
                         G4ParticleDefinition* ion    = G4IonTable::GetIonTable()->GetIon(Z,A,excitEnergy);
                        fParticleGun->SetParticleDefinition(ion);
                        fParticleGun->SetParticleCharge(ionCharge);
                        
                        fParticleGun->GeneratePrimaryVertex(anEvent);
	}
	
	if(seed3<1)
	{
		G4double theta = 2*CLHEP::pi*G4UniformRand();
                G4double radii = 19.05*G4UniformRand();
                G4double height = 38.1*G4UniformRand();  
		fParticleGun->SetParticlePosition(G4ThreeVector(radii*std::cos(theta)*mm,radii*std::sin(theta)*mm,(height+21.5)*mm));

		fParticleGun->SetParticleMomentumDirection(G4ThreeVector(1.,0.,0.));

                         G4int Z = 57, A = 138;
                        G4double ionCharge   = 0.*eplus;
                        G4double excitEnergy = 0.*keV; 

                         G4ParticleDefinition* ion    = G4IonTable::GetIonTable()->GetIon(Z,A,excitEnergy);
                        fParticleGun->SetParticleDefinition(ion);
                        fParticleGun->SetParticleCharge(ionCharge);

                        fParticleGun->GeneratePrimaryVertex(anEvent);
	        }
	
	

	/*else if(seed>=90&&seed<95) 
	{
		fParticleGun->SetParticlePosition(G4ThreeVector(0.*mm,0.*mm,0.*mm));
                fParticleGun->SetParticleMomentumDirection(G4ThreeVector(0.,0.,1.));

                        G4int Z = 27, A = 60;
                        G4double ionCharge   = 0.*eplus;
                        G4double excitEnergy = 0.*keV;

                        G4ParticleDefinition* ion
                                = G4IonTable::GetIonTable()->GetIon(Z,A,excitEnergy);
                        fParticleGun->SetParticleDefinition(ion);
                        fParticleGun->SetParticleCharge(ionCharge);

			fParticleGun->GeneratePrimaryVertex(anEvent);

		G4double theta = 2*CLHEP::pi*G4UniformRand();
		G4double radii = 19.05*G4UniformRand();   
		G4double height = 38.1*G4UniformRand();
	
		G4int seed1 = rand()%2;
		
		if(seed1==0)
		{
			fParticleGun->SetParticlePosition(G4ThreeVector(radii*std::cos(theta)*mm,radii*std::sin(theta)*mm,(height-59.6)*mm));
		}
		else
		{
		
			fParticleGun->SetParticlePosition(G4ThreeVector(radii*std::cos(theta)*mm,radii*std::sin(theta)*mm,(height+21.5)*mm));
		}
		fParticleGun->SetParticleMomentumDirection(G4ThreeVector(1.,0.,0.));          

			 Z = 57, A = 138;

			 ion	= G4IonTable::GetIonTable()->GetIon(Z,A,excitEnergy);
			fParticleGun->SetParticleDefinition(ion);
			fParticleGun->SetParticleCharge(ionCharge);
			
			fParticleGun->GeneratePrimaryVertex(anEvent);
	}
	
	else if(seed>=95&&seed<100) 
        {
		G4double theta = 2*CLHEP::pi*G4UniformRand();
                G4double radii = 19.05*G4UniformRand();
                G4double height = 38.1*G4UniformRand();		
		G4int seed1 = rand()%2;
                if(seed1==0)
                {
                        fParticleGun->SetParticlePosition(G4ThreeVector(radii*std::cos(theta)*mm,radii*std::sin(theta)*mm,(height-59.6)*mm));
                }
                else
                {

                        fParticleGun->SetParticlePosition(G4ThreeVector(radii*std::cos(theta)*mm,radii*std::sin(theta)*mm,(height+21.5)*mm));
                }
                fParticleGun->SetParticleMomentumDirection(G4ThreeVector(1.,0.,0.));

                         G4int Z = 57, A = 138;
			G4double ionCharge   = 0.*eplus;
                        G4double excitEnergy = 0.*keV;


                         G4ParticleDefinition* ion    = G4IonTable::GetIonTable()->GetIon(Z,A,excitEnergy);
                        fParticleGun->SetParticleDefinition(ion);
                        fParticleGun->SetParticleCharge(ionCharge);

                        fParticleGun->GeneratePrimaryVertex(anEvent);
        }	

*/


	
	//create vertex
	//   
}
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
