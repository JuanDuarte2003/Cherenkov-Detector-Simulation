/*
    Cherenkov Simulation
*/

#ifndef T1SteppingAction_h
#define T1SteppingAction_h 1

// Geant4 Headers
#include "G4UserSteppingAction.hh"
#include "globals.hh"
#include "G4VPhysicalVolume.hh"

class G4LogicalVolume;

/// Stepping action class

namespace T1
{
    class T1EventAction;

    class T1SteppingAction : public G4UserSteppingAction
    {
    public:
        T1SteppingAction(T1EventAction *eventAction);
        ~T1SteppingAction() override = default;

        // method from the vase class
        void UserSteppingAction(const G4Step *) override;

    private:
        T1EventAction *fEventAction;
        vector<G4LogicalVolume *> fScoringVolumeVector;
    };

}

#endif