#include "globals.hh"

#include "G4RunManager.hh"
#include "G4VisExecutive.hh"
#include "G4UImanager.hh"
#include "G4UIExecutive.hh"

#include "DetectorConstruction.hh"
#include "PrimaryGeneratorAction.hh"
#include "RunAction.hh"
#include "SteppingAction.hh"
#include "PhysicsList.hh"

#include "g4root.hh"
using namespace std;

int main(int argc, char** argv)
{
  CLHEP::HepRandom::setTheEngine(new CLHEP::RanecuEngine);
  //----------------------
  G4String filename = "data";
    for(G4int i = 1;i < argc;i=i+2){
      if(G4String(argv[i])=="-r")
      {
        G4Random::setTheSeed(atof(argv[i+1]));
        G4cout << atof(argv[i+1]) << G4endl; 
      }
      else if(G4String(argv[i])=="-f")
      {
        filename = argv[i+1]; 
      }
    }
  G4AnalysisManager::Instance()->SetFileName(filename);
  //---------------------
  G4RunManager* runManager = new G4RunManager;

  cout << "Instantiating DetectorConstuction ..." << endl;
  DetectorConstruction* detector = new DetectorConstruction();
  runManager -> SetUserInitialization(detector);
  cout << "... Done." << endl;

  cout << "Instantiating PhysicsList ..." << endl;
  PhysicsList* physicslist = new PhysicsList();
  runManager -> SetUserInitialization(physicslist);
  cout << "... Done." << endl;

  cout << "Primary Generator ..." << endl;
  runManager -> SetUserAction(new PrimaryGeneratorAction());
  cout << "... Done." << endl;

  cout << "Run Action ..." << endl;
  runManager -> SetUserAction(new RunAction());
  cout << "... Done." << endl;

  cout << "Stepping Action ..." << endl;
  runManager -> SetUserAction(new SteppingAction());
  cout << "... Done." << endl;

  runManager->Initialize();


  G4VisManager* visManager = new G4VisExecutive;
  visManager -> Initialize();

  G4UImanager* UImanager = G4UImanager::GetUIpointer();
  /*----------------------------------------
  if (argc != 1)
  {
    G4String command = "/control/execute ";
    G4String fileName = argv[1];
    UImanager -> ApplyCommand(command+fileName);
  }
  else
  {
    G4UIExecutive* ui = new G4UIExecutive(argc, argv);
    UImanager -> ApplyCommand("/control/execute vis.mac");
    ui -> SessionStart();
    delete ui;
  }
  */
  if (1)
  {
    UImanager -> ApplyCommand("/control/execute run.mac");
  }
  else
  {
    G4UIExecutive* ui = new G4UIExecutive(argc, argv);
    UImanager -> ApplyCommand("/control/execute vis.mac");
    ui -> SessionStart();
    delete ui;
  }
  delete visManager;
  delete runManager;

  return 0;
}
