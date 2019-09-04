#include "SteppingAction.hh"

#include "G4Event.hh"
#include "G4RunManager.hh"
#include "G4SystemOfUnits.hh"
#include "G4RunManager.hh"

SteppingAction::SteppingAction()
: G4UserSteppingAction()
{
}

SteppingAction::~SteppingAction()
{
}

void SteppingAction::UserSteppingAction(const G4Step* step)
{
	G4int eventID = G4RunManager::GetRunManager() -> GetCurrentEvent() -> GetEventID();
	//G4int particleID = step -> GetTrack() -> GetParticleDefinition() -> GetPDGEncoding();
	G4int volumeID = step -> GetPreStepPoint() -> GetPhysicalVolume() -> GetCopyNo();
	G4double totalEdep = 1000*(step -> GetTotalEnergyDeposit());


	G4AnalysisManager* analysisManager = G4AnalysisManager::Instance();
	if(volumeID==100||volumeID==200)
{
	analysisManager -> FillNtupleIColumn(0, eventID);
	analysisManager -> FillNtupleIColumn(1, volumeID);
	//analysisManager -> FillNtupleIColumn(2, particleID);
	analysisManager -> FillNtupleDColumn(2, totalEdep);
	analysisManager -> AddNtupleRow();
}


}
