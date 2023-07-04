// --------------------------------------------------------------
//   GEANT 4 - Germanium Detector at IFUNAM
//									
//      For information related to this code contact: 
//	José Luis Hernández and Osmany González Reina
//      e-mail: luis.hernandez@ciencias.unam.mx
// --------------------------------------------------------------
// Comments
//
//                     Germanium Detector
//                    (17th September 2018)
//
// DetectorConstruction program
// --------------------------------------------------------------

#include "DMXDetectorConstruction.hh"
#include "DMXDetectorMessenger.hh"
#include "DMXScintSD.hh"
#include "DMXPmtSD.hh"
#include "G4Material.hh"
#include "G4NistManager.hh"
#include "G4MaterialTable.hh"
#include "G4Element.hh"
#include "G4Isotope.hh"
#include "G4UnitsTable.hh"
#include "G4Box.hh"
#include "G4Tubs.hh"
#include "G4Sphere.hh"
#include "G4Polycone.hh"
#include "G4UnionSolid.hh"
#include "G4MultiUnion.hh"
#include "G4SubtractionSolid.hh"
#include "G4LogicalVolume.hh"
#include "G4PVPlacement.hh"
#include "G4ThreeVector.hh"
#include "G4RotationMatrix.hh"
#include "G4Transform3D.hh"
#include "G4LogicalBorderSurface.hh"
#include "G4LogicalSkinSurface.hh"
#include "G4OpBoundaryProcess.hh"
#include "G4FieldManager.hh"
#include "G4UniformElectricField.hh"
#include "G4TransportationManager.hh"
#include "G4MagIntegratorStepper.hh"
#include "G4EqMagElectricField.hh"
#include "G4ClassicalRK4.hh"
#include "G4ChordFinder.hh"
#include "G4SDManager.hh"
#include "G4VisAttributes.hh"
#include "G4Colour.hh"
#include "G4UserLimits.hh"
#include "G4RunManager.hh"
#include "G4SystemOfUnits.hh"

#include <math.h>
#define PI 3.14159265

DMXDetectorConstruction::DMXDetectorConstruction()  
{


  theUserLimitsForRoom     = 0; 
  theUserLimitsForDetector = 0; 
  theMaxTimeCuts      = DBL_MAX;
  theMaxStepSize      = DBL_MAX;
  theDetectorStepSize = DBL_MAX;
  theRoomTimeCut      = 1000. * nanosecond;
  theMinEkine         = 250.0*eV;
  theRoomMinEkine     = 250.0*eV;
  LXeSD.Put(0);                   

}

DMXDetectorConstruction::~DMXDetectorConstruction() 
{
  delete theUserLimitsForRoom;
  delete theUserLimitsForDetector;
  delete detectorMessenger;
}

void DMXDetectorConstruction::DefineMaterials() 
{

 #include "DMXDetectorMaterial.icc"

}

G4VPhysicalVolume* DMXDetectorConstruction::Construct() {

  DefineMaterials();
 
  G4Colour  white   (1.0, 1.0, 1.0) ;
  G4Colour  grey    (0.5, 0.5, 0.5) ;
  G4Colour  lgrey   (.85, .85, .85) ;
  G4Colour  red     (1.0, 0.5, 0.0) ;
  G4Colour  blue    (0.0, 0.0, 1.0) ;
  G4Colour  cyan    (0.0, 1.0, 1.0) ;
  G4Colour  magenta (1.0, 0.0, 1.0) ; 
  G4Colour  yellow  (1.0, 1.0, 0.0) ;
  G4Colour  orange  (.9, 0.2, 0.0) ;
  G4Colour  lblue   (0.0, 0.0, .75) ;
  G4Colour  lgreen  (0.0, .75, 0.0) ;
  G4Colour  green   (0.0, 1.0, 0.0) ;
  G4Colour  brown   (0.7, 0.4, 0.1) ;


  G4double wallThick   = 24.*cm;
  G4double worldWidth  = 470.0*cm + 2.*wallThick; 
  G4double worldLength = 690.0*cm + 2.*wallThick; 
  G4double worldHeight = 280.0*cm + 2.*wallThick; 
 
  G4bool checkOverlaps = true;

  G4RotationMatrix* rotation = new G4RotationMatrix();
  rotation->rotateX(90.*deg);
  rotation->rotateY(0.*deg);
  rotation->rotateZ(0.*deg);

  G4Box* world_box = new G4Box("world_box", 0.5*worldWidth, 0.5*worldLength, 0.5*worldHeight );
  world_log  = new G4LogicalVolume(world_box, world_mat, "world_log");
  world_phys = new G4PVPlacement(0, G4ThreeVector(0.,0.,0.),"world_phys", world_log, NULL, false, checkOverlaps);
  G4VisAttributes* world_vat= new G4VisAttributes(white);
  world_vat->SetVisibility(true);
  world_log->SetVisAttributes(world_vat);

  G4double labWidth  = worldWidth  - 2.*wallThick; 
  G4double labLength = worldLength - 2.*wallThick;
  G4double labHeight = worldHeight - 2.*wallThick; 

  G4Box* lab_box = new G4Box("lab_box", 0.5*labWidth, 0.5*labLength, 0.5*labHeight );
  lab_log  = new G4LogicalVolume(lab_box, lab_mat, "lab_log");
  lab_phys = new G4PVPlacement(0, G4ThreeVector(0.,0.,0.), "lab_phys",lab_log, world_phys, false,checkOverlaps);

  G4VisAttributes* covercylindercolor= new G4VisAttributes(gray);
  covercylindercolor->SetVisibility(true);

  G4double covercylinderinnerradius = 0.0*cm;//3.9675*cm; 
  G4double covercylinderouterradius = 4.1275*cm;
  G4double covercylinderheight = 23.70*cm;
  G4Tubs* covercylinder = new G4Tubs("covercylinder", covercylinderinnerradius, covercylinderouterradius, covercylinderheight/2.,  0.*deg, 360.*deg);
  covercylinderlog = new G4LogicalVolume(covercylinder, panel_mat,"covercylinderlog");
  covercylinderphys = new G4PVPlacement(0, G4ThreeVector(), "covercylinderphys", covercylinderlog, lab_phys, false, checkOverlaps); 
  covercylinderlog->SetVisAttributes(covercylindercolor);

  G4double covertube_out_innerradius = 3.1975*cm; //9.3 mm measured for endcap on face
  G4double covertube_out_outerradius = 4.1275*cm;
  G4double covertube_out_height = 1.6*mm;
  G4Tubs* covertube_out = new G4Tubs("covertube_out", covertube_out_innerradius, covertube_out_outerradius, covertube_out_height/2.,  0.*deg, 360.*deg);
  covertube_out_log = new G4LogicalVolume(covertube_out, panel_mat,"covertube_out_log");
  covertube_out_phys = new G4PVPlacement(0, G4ThreeVector(0,0,11.85*cm+(0.5*covertube_out_height)), "covertube_out_phys", covertube_out_log, lab_phys, false, checkOverlaps); 
  covertube_out_log->SetVisAttributes(covercylindercolor);

  
  G4VisAttributes* cryostatwindowcolor= new G4VisAttributes(blue);
  cryostatwindowcolor->SetVisibility(true);
  G4double cryostatwindowinnerradius = 0*cm;
  G4double cryostatwindowouterradius = 3.1975*cm; //it is 3.9675, embedded in the aluminum 
  G4double cryostatwindowheight = 0.6*mm;
  G4Tubs* cryostatwindowsolid = new G4Tubs("cryostatwindowsolid", cryostatwindowinnerradius, cryostatwindowouterradius, cryostatwindowheight/2.,  0.*deg, 360.*deg);
  cryostatwindowlog = new G4LogicalVolume(cryostatwindowsolid, cryostatwindow,"cryostatwindowLog");
  cryostatwindowphys = new G4PVPlacement(0, G4ThreeVector(0.*cm,0*cm,11.85*cm+0.5*covertube_out_height), "cryostatwindowphys", cryostatwindowlog, lab_phys, false, checkOverlaps); 
  cryostatwindowlog->SetVisAttributes(cryostatwindowcolor);

  
  G4VisAttributes* vacuumtubecolor= new G4VisAttributes(white);
  vacuumtubecolor->SetVisibility(true);
  G4double vacuumtubeinnerradius = 0.0*cm;
  G4double vacuumtubeouterradius = 3.9675*cm;
  G4double vacuumtubeheight = 23.70*cm;
    
  G4Tubs* vacuumtube = new G4Tubs("vacuumtube", vacuumtubeinnerradius, vacuumtubeouterradius, vacuumtubeheight/2.,  0.*deg, 360.*deg);
  vacuumtube_log = new G4LogicalVolume(vacuumtube, vacuum_mat,"vacuumtube_log");
  vacuumtube_phys = new G4PVPlacement(0, G4ThreeVector(), "vacuumtube_phys", vacuumtube_log, covercylinderphys, false, checkOverlaps); 
  vacuumtube_log->SetVisAttributes(vacuumtubecolor);

  G4VisAttributes* BEGeDeadcolor= new G4VisAttributes(gray);
  BEGeDeadcolor->SetVisibility(true);
  G4double BEGeDeadInnerRadius = 0.0*cm;
  G4double BEGeDeadOuterRadius = 3.0*cm;
  G4double BEGeDeadHeight = 2.0*cm;
  G4Tubs* BEGeDeadTube = new G4Tubs("BEGeDeadTube", BEGeDeadInnerRadius,  BEGeDeadOuterRadius,  BEGeDeadHeight/2.,  0.*deg, 360.*deg);
  BEGeDeadLog = new G4LogicalVolume(BEGeDeadTube, BEGe_mat ,"BEGeDeadLog");
  BEGeDeadPhys = new G4PVPlacement(0, G4ThreeVector(0.*cm,0.*cm,10.46*cm), "BEGeDeadPhys", BEGeDeadLog, vacuumtube_phys, false, checkOverlaps);
  BEGeDeadLog->SetVisAttributes(BEGeDeadcolor);
  //10.46 = 11.85cm + 0.5*covertube_out_heigh + 0.5*cryostatwindowheight - 5 mm (from drawing) - 1 cm (half of radius)
  
  G4VisAttributes* BEGecolor= new G4VisAttributes(red);
  BEGecolor->SetVisibility(true);
  G4double BEGeFrontLayer =0.0003*mm; /* Front dead layer as per drawing */
  //G4double BEGeFrontLayer =0.12*cm; /* augmented dead layer */
  G4double BEGeBackLayer = 0.05*cm; /* Side and back dead layer as per drawing */
  //G4double BEGeBackLayer = 2.00*mm; /* Side and back dead layer as per drawing */
  G4double BEGeInnerRadius = 0.0*cm;
  G4double BEGeOuterRadius =  BEGeDeadOuterRadius- BEGeBackLayer; //2.95*cm;
  G4double BEGeHeight = BEGeDeadHeight - BEGeBackLayer - BEGeFrontLayer;
  G4Tubs* BEGeTube = new G4Tubs("BEGeTube", BEGeInnerRadius,  BEGeOuterRadius,  BEGeHeight/2.,  0.*deg, 360.*deg);
  BEGeLog = new G4LogicalVolume(BEGeTube, BEGe_mat ,"BEGeLog");
  G4double BEGeZPosition = BEGeBackLayer/2 - BEGeFrontLayer/2;
  BEGePhys = new G4PVPlacement(0, G4ThreeVector(0.*cm,0.*cm,BEGeZPosition), "BEGePhys", BEGeLog, BEGeDeadPhys, false, checkOverlaps); 
  BEGeLog->SetVisAttributes(BEGecolor);

  G4VisAttributes* IRwindowcolor= new G4VisAttributes(cyan);
  IRwindowcolor->SetVisibility(true);
  G4double BoPETwindowinnerradius = 0.0*cm;
  G4double BoPETwindowouterradius = 3.0*cm;
  G4double BoPETwindowheight = 0.0074*mm;
  G4Tubs*  BoPETwindow = new G4Tubs("BoPETwindow", BoPETwindowinnerradius,  BoPETwindowouterradius, BoPETwindowheight/2.,  0.*deg, 360.*deg);
  BoPETwindow_log = new G4LogicalVolume(BoPETwindow, polyethylene_mat ,"BoPETwindow_log");
  BoPETwindow_phys = new G4PVPlacement(0, G4ThreeVector(0.*cm,0.*cm,11.46*cm+(BoPETwindowheight/2)), "BoPETwindow_phys", BoPETwindow_log, vacuumtube_phys, false, checkOverlaps);  
  BoPETwindow_log->SetVisAttributes(covercylindercolor);

  G4double IRwindowinnerradius = 0.0*cm;
  G4double IRwindowouterradius = 3.0*cm;
  G4double IRwindowheight = 0.0001*mm; // 100 nm of aluminum
  G4Tubs*  IRwindow = new G4Tubs("IRwindow", IRwindowinnerradius,  IRwindowouterradius, IRwindowheight/2.,  0.*deg, 360.*deg);
  IRwindow_log = new G4LogicalVolume(IRwindow, panel_mat ,"IRwindow_log");
  IRwindow_phys = new G4PVPlacement(0, G4ThreeVector(0.*cm,0.*cm,11.46*cm+(BoPETwindowheight)+(IRwindowheight/2)), "IRwindow_phys", IRwindow_log, vacuumtube_phys, false, checkOverlaps);  
  IRwindow_log->SetVisAttributes(IRwindowcolor);
  
  
  G4VisAttributes* sourcecolor= new G4VisAttributes(orange);
  sourcecolor->SetVisibility(true);
  G4double sourcex = 1.9*mm; 
  G4double sourcey = 23.5*mm; 
  G4double sourcez = 11.1*mm;

  G4RotationMatrix* sourceRot = new G4RotationMatrix;               
  sourceRot->rotateX(PI/2.*rad);
  sourceRot->rotateZ(PI/2.*rad);

  //G4double sourcePosZ = 11.845*cm + 15.00*cm - (1.9*mm/2.);
  //G4double sourcePosZ = 11.94*cm + 5.00*cm - 1.9*mm;
  G4double sourcePosZ = 11.85*cm + (1.6*mm/2.) + (0.6*mm/2.) + 5.00*cm - (1.9*mm/2.);
    
  G4Box* source = new G4Box("source", sourcex/2 , sourcey/2 , sourcez/2);
  source_log  = new G4LogicalVolume(source, glass_port_mat, "source_log");
  source_phys = new G4PVPlacement(sourceRot, G4ThreeVector(0, 0, sourcePosZ),  "source_phys",source_log, lab_phys, false,checkOverlaps); 
  source_log->SetVisAttributes(sourcecolor);



  return world_phys;

}

void DMXDetectorConstruction::ConstructSDandField()	
{
    if (LXeSD.Get() == 0)
      {
        G4String name="/DMXDet/LXeSD";
        DMXScintSD* aSD = new DMXScintSD(name);
        LXeSD.Put(aSD);
      }
    G4SDManager::GetSDMpointer()->AddNewDetector(LXeSD.Get());
    if (BEGeLog)
      SetSensitiveDetector(BEGeLog,LXeSD.Get());

    return;

}



