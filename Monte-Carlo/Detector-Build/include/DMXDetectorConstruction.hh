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
//
// --------------------------------------------------------------
//   GEANT 4 - Underground Dark Matter Detector Advanced Example
//
//      For information related to this code contact: Alex Howard
//      e-mail: alexander.howard@cern.ch
// --------------------------------------------------------------
// Comments
//
//                  Underground Advanced
//               by A. Howard and H. Araujo 
//                    (27th November 2001)
//
// DetectorConstruction header
// --------------------------------------------------------------

#ifndef DMXDetectorConstruction_h
#define DMXDetectorConstruction_h 1

#include "G4VUserDetectorConstruction.hh"
#include "globals.hh"
#include "G4Cache.hh"

class G4LogicalVolume;
class G4VPhysicalVolume;
class G4Material;

class G4UserLimits;

class DMXScintSD;
class DMXPmtSD;

class DMXDetectorMessenger;

class DMXDetectorConstruction : public G4VUserDetectorConstruction 
{
public:

  DMXDetectorConstruction();
  ~DMXDetectorConstruction();

public:

  G4VPhysicalVolume* Construct();
  void ConstructSDandField();

  void SetRoomEnergyCut(G4double);
  void SetEnergyCut(G4double);
  void SetTimeCut(G4double);
  void SetRoomTimeCut(G4double);
 
private:

  void DefineMaterials();

  G4UserLimits*    theUserLimitsForRoom; 
  G4UserLimits*    theUserLimitsForDetector; 
  //  G4UserLimits*    theUserLimitsForXenon; 

  G4double         theMaxTimeCuts;
  G4double         theMaxStepSize;
  G4double         theDetectorStepSize;
  G4double         theMinEkine;
  G4double         theRoomMinEkine;
  
  G4double         theRoomTimeCut;


#include "DMXDetectorMaterial.ihh"  // materials used

  G4double sourceZ;
  G4LogicalVolume*   world_log;        // pointers
  G4VPhysicalVolume* world_phys;  

#include "DMXDetectorRoom.ihh"


  G4LogicalVolume*   logicWorld;
  G4VPhysicalVolume* physWorld;
  G4LogicalVolume*   lab_log;
  G4VPhysicalVolume* lab_phys;
  G4LogicalVolume*   STLhousinglog;
  G4VPhysicalVolume* STLhousingphys;
  G4LogicalVolume*   NaIcrystallog;
  G4VPhysicalVolume* NaIcrystalphys;
  G4LogicalVolume* Optical_Windowlog;
  G4VPhysicalVolume* Optical_Windowphys;
  G4LogicalVolume* OPTIFClog;
  G4VPhysicalVolume* OPTIFCphys;
  G4LogicalVolume* AcrylicBoxlog;
  G4VPhysicalVolume* AcrylicBoxphys;
  G4LogicalVolume* AcrylicBoxInsidelog;
  G4VPhysicalVolume* AcrylicBoxInsidephys;
  G4LogicalVolume* Springlog;
  G4VPhysicalVolume* Springphys;
  G4LogicalVolume* sourcelog;
  G4VPhysicalVolume* sourcephys;
  G4LogicalVolume* DLSlog;
  G4VPhysicalVolume* DLSphys;

 





  G4Cache<DMXScintSD*> LXeSD; //pointer to sensitive detectors


  // pointer to the Detector Messenger:
  DMXDetectorMessenger*  detectorMessenger;

};

#endif

