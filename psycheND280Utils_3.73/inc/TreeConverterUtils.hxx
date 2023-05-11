#ifndef TreeConverterUtils_h
#define TreeConverterUtils_h

#include "BaseDataClasses.hxx"
#include "ND280AnalysisUtils.hxx"
#include "SubDetId.hxx"

/// This namespace contains useful functions for analyses. 
/// This is in addition to those defined in psycheUtils
namespace convUtils{

    
    /// Convert the detector used array to the bit field used by psyche for TPC track segments
    void ConvertTPCDetEnumToBitField(unsigned long &det, int tpc);
    /// Convert the detector used array to the bit field used by psyche for FGD track segments
    void ConvertFGDDetEnumToBitField(unsigned long &det, int fgd);
    /// Convert the detector used array to the bit field used by psyche for SMRD track segments
    void ConvertSMRDDetEnumToBitField(unsigned long &det, int smrd);
    /// Convert the detector used array to the bit field used by psyche for ECAL track segments
    void ConvertECALDetEnumToBitField(unsigned long &det, int ecal); 
    
    /// Convert the detector used array to the bit field used by psyche given a SubDetEnum
    void ConvertLocalDetEnumToBitField(unsigned long &det, int index, SubDetId::SubDetEnum subdet_enum); 

    /// Convert the detector used array to the bit field used by psyche for truth trueParts
    void ConvertTrueParticleDetEnumToBitField(unsigned long &det, int DetUsed);
    
    /// Convert the detector used array to the bit field used by psyche for tracker tracks
    void ConvertTrackerDetEnumToBitField(unsigned long &det, int DetUsed);
   
    /// Convert tracker detector field to bit field 
    void ConvertTrackerDetFieldToBitField(unsigned long &det, int Detectors);

    /// Convert the detector used array to the bit field used by psyche for ana tracks
    void ConvertTrackDetEnumToBitField(unsigned long &det, int DetUsed[]);
    /// Convert the detector used array to the bit field used by psyche for ana tracks
    void ConvertTrackDetEnumToBitField(unsigned long &det, bool DetUsed[]);
    /// Set the bit field for a used detector given oaAnalysis detector enumeration (TGlobalPID::DetectorUsed)
    void SetDetectorUsedField(unsigned long &det, unsigned int i);
    /// Get old local detector enumeration to find array index of Flat tree  
    int GetLocalDetEnum(SubDetId::SubDetEnum det, SubDetId::SubDetEnum idet);

    /// Get highland style tracker combination numbering
    void ConvertBitFieldToTrackerDetField(unsigned long det, int& trackerDet);

    /// Get highland style numbering for true objects
    void ConvertBitFieldToTrueParticleDetEnum(unsigned long det, int &trueDet);

}
#endif


