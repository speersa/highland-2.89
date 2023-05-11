#ifndef ND280GeomIdDef_hxx_seen
#define ND280GeomIdDef_hxx_seen

namespace ND {
    namespace GeomId {
        /// Define the fields used to create a unique identifier for elements
        /// in the ND280 geometry.  This is a 32 bit field with the bits
        /// number from 0 (least significant bit or LSB) to 31 (most
        /// significant bit or MSB).  The bit fields are defined as follows
        ///
        /// \code 
        /// r dddddd sssssssssssssssssssssssss
        /// r(1)  -- Reserved
        /// d(6)  -- The sub-detector identifier
        /// s(25) -- The sub-detector specific field
        /// \endcode
        ///
        /// The value of all constants and order of all enumerations defined
        /// below is significant and must not be changed.
        namespace Def {
#define MAKE_MASK(msb,lsb) (((1<<(((msb)-(lsb))+1))-1)<<(lsb))
        
            /// A bitwise mask for a field;
            typedef unsigned long GeomIdMask;
        
            /// Bit number.  The bits are counted 0 (LSB) to 31 (MSB)
            typedef unsigned long GeomIdBit;
        
            /// A value that can be used to initialize an empty geometry
            /// identifier.
            const GeomIdMask   kEmptyId = 0;

            /// The most significant bit of the reserved guard bit.
            const GeomIdBit   kReserved1MSB = 31;
            /// The least significant bit of the reserved guard bit.  This bit
            /// must be zero for a geometry Id.  The value of 1 is reserved
            /// for future use to indicate an electronics channel number.
            const GeomIdBit   kReserved1LSB = 31;
        
            /// The mask to select the first reserved field.  The value in the
            /// first reserved field must be zero.
            const GeomIdMask kReserved1Mask 
            = MAKE_MASK(kReserved1MSB,kReserved1LSB);

            /// The most significant bit of the detector identifier.  This is
            /// a 6 bit field.
            const GeomIdBit   kDetectorIdMSB = kReserved1LSB-1;

            /// The least significant bit of the detector identifier.
            const GeomIdBit   kDetectorIdLSB = kDetectorIdMSB-5;

            /// The mask to select the detector identifier
            const GeomIdMask kDetectorIdMask 
            = MAKE_MASK(kDetectorIdMSB,kDetectorIdLSB);

            /// Enumeration defining the detector identifiers.  The detector
            /// identifiers are used to uniquely define which sub-detector
            /// containes a geometry element.  All geometry elements are by
            /// definition within a single sub-detector.  The identifiers are
            /// held in the bit field defined by DetectorMask.  The conversion
            /// from a sub-detector identifier to a field value is
            /// (value<<DetectorLSB).  The conversion from a field value to a
            /// sub-detector identifier is ((field&DetectorMask)>>DetectorLSB)
            enum DetectorId {
                kROOTGeoNodeId = 0,
                kP0D,
                kTPC,
                kFGD,
                kDSECal,
                kTECal,
                kPECal,
                kSMRD,
                kINGRID
            };

            /// The most significant bit in the field reserved to the
            /// sub-detector.
            const GeomIdBit kSubDetectorMSB = kDetectorIdLSB-1;
            /// The least significant bit in the field reserved to the
            /// sub-detector.
            const GeomIdBit kSubDetectorLSB = 0;
        
            /// The mask to select the sub-detector detector fields.
            const GeomIdMask kSubDetectorMask = MAKE_MASK(kSubDetectorMSB,
                                                          kSubDetectorLSB);
        
            /// Define the p0d specific constants used to decode a geometry
            /// identifier.  The P0D field is 25 bits divided into a sequence
            /// identifier, and a field value.
            ///
            /// \code
            /// sssss ffffffffffffffffffff
            /// s(4)  -- The sequence identifier (0 to 15)
            /// f(21) -- The field value associated with a sequence id.
            /// \endcode
            ///
            /// Depending on the particular sequence, the field values may be
            /// further sub-divided.
            namespace P0D {
                /// Define the sequences required in the P0D.
                enum P0DSeqId {
                    /// A global volume.  This is used for identifiers that
                    /// refer to volumes which contain other geometry
                    /// identifiers.
                    kGlobal = 0,
                    /// A scintillator bar.
                    kScintillator,
                };

                /// The most significant bit of the sequence identifier field.
                /// The sequence id field can have values between 0-15.
                const GeomIdBit kSeqIdMSB = Def::kSubDetectorMSB;
                const GeomIdBit kSeqIdLSB = kSeqIdMSB - 3;
                const GeomIdMask kSeqIdMask = MAKE_MASK(kSeqIdMSB,kSeqIdLSB);

                /// A field that is unique to each global volume.  A global
                /// volume is any volume (with a geometry identifier) that
                /// contains other volumes with geometry identifiers.
                /// Examples are the super-P0Dules, and the P0Dules.  The bits
                /// are defined as
                ///
                /// \code
                /// gggggggg fffffffffff
                /// g(8)  -- The type of global volume.
                /// f(13) -- The field value.
                /// \endcode
                namespace Global {
                    /// @{ Define a field to hold the type of global volume
                    /// being identified.
                    const GeomIdBit kSeqIdMSB = Def::P0D::kSeqIdLSB-1;
                    const GeomIdBit kSeqIdLSB = kSeqIdMSB-7;
                    const GeomIdMask kSeqIdMask=MAKE_MASK(kSeqIdMSB,kSeqIdLSB);
                    /// @}
                
                    enum GlobalSeqId {
                        /// A special case for one of a kind global volumes
                        kP0D,
                        /// One of the super-P0Dules
                        kSP0Dule,
                        /// One of the P0Dules
                        kP0Dule,
                        /// One of the water target modules
                        kTarget,
                        /// One of the ECal Radiators
                        kECalRadiator,
                        /// One of the brass target radiators
                        kTargetRadiator,
                    };
                
                    /// @{ The sequence value for this type of global volume.
                    const GeomIdBit kFieldMSB = kSeqIdLSB-1;
                    const GeomIdBit kFieldLSB = 0;
                    const GeomIdMask kFieldMask=MAKE_MASK(kFieldMSB,kFieldLSB);
                    /// @}
                };

                /// A field that is unique for each scintillator bar.
                /// \code
                /// sss x pppppp bbbbbbbbbbb
                /// s(3) -- The super-P0Dule (0 to 3)
                /// x(1) -- The layer in the super P0Dule (0=x, 1=y)
                /// p(6) -- The P0Dule (0 to 40)
                /// b(11) -- The bar number (0 to 125 or 0 to 133)
                /// \endcode
                namespace Bar {
                    /// @{ The super-P0Dule number within the detector.  The
                    /// numbering starts at the upstream end and starts from
                    /// zero.  0) USECal, 1) USWT, 2) CWT, 3) CECal
                    const GeomIdBit kSP0DuleMSB = Def::P0D::kSeqIdLSB-1;
                    const GeomIdBit kSP0DuleLSB = kSP0DuleMSB-2;
                    const GeomIdMask kSP0DuleMask = MAKE_MASK(kSP0DuleMSB,
                                                              kSP0DuleLSB);
                    /// @}

                    /// @{ The layer within the P0Dule. Layer zero is X, and
                    /// layer one is Y.
                    const GeomIdBit kLayerMSB = kSP0DuleLSB-1;
                    const GeomIdBit kLayerLSB = kLayerMSB;
                    const GeomIdMask kLayerMask=MAKE_MASK(kLayerMSB,kLayerLSB);
                    /// @}

                    /// @{ The P0Dule number within the super-P0Dule.  The
                    /// P0Dule numbering starts from zero.
                    const GeomIdBit kP0DuleMSB = kLayerLSB-1;
                    const GeomIdBit kP0DuleLSB = kP0DuleMSB-5;
                    const GeomIdMask kP0DuleMask = MAKE_MASK(kP0DuleMSB,
                                                             kP0DuleLSB);
                    /// @}

                    /// @{ Define the field to hold the bar number within a
                    /// layer.  The bars are numbered 0 to 125 (or 133) with
                    /// Bar 0 at the most negative coordinate.
                    const GeomIdBit kBarMSB = kP0DuleLSB-1;
                    const GeomIdBit kBarLSB = kBarMSB-10;
                    const GeomIdMask kBarMask = MAKE_MASK(kBarMSB,kBarLSB);
                    /// @}
                };            
            };

            /// Define the TPC specific constants used to decode a geometry
            /// identifier.
            namespace TPC {
                /// Define the sequences required in the TPC.
                enum TPCSeqId {
                    /// A global volume.  This is used for identifiers that
                    /// refer to volumes which contain other geometry
                    /// identifiers.
                    kGlobal = 0,
                    /// A micromega pad.
                    kPad,
                };

                /// The most significant bit of the sequence identifier field.
                /// The sequence id field can have values between 0-15.
                const GeomIdBit kSeqIdMSB = Def::kSubDetectorMSB;
                const GeomIdBit kSeqIdLSB = kSeqIdMSB - 3;
                const GeomIdMask kSeqIdMask = MAKE_MASK(kSeqIdMSB,kSeqIdLSB);

                namespace Global {
                    /// @{ Define a field to hold the type of global volume
                    /// being identified.
                    const GeomIdBit kSeqIdMSB = Def::TPC::kSeqIdLSB-1;
                    const GeomIdBit kSeqIdLSB = kSeqIdMSB-7;
                    const GeomIdMask kSeqIdMask=MAKE_MASK(kSeqIdMSB,kSeqIdLSB);
                    /// @}
                
                    enum GlobalSeqId {
                        /// One of the TPC overall volumes (TPC1, TPC2, or TPC3)
                        kTPC,
                    };
                
                    /// @{ The sequence value for this type of global volume.
                    const GeomIdBit kFieldMSB = kSeqIdLSB-1;
                    const GeomIdBit kFieldLSB = 0;
                    const GeomIdMask kFieldMask=MAKE_MASK(kFieldMSB,kFieldLSB);
                    /// @}
                };

                /// A field that is unique for each TPC micromega pad.
                ///
                /// \code
                /// sss x f ppppp bbbbbbbbbbb
                /// s(3) -- The tpc (0 to 2)
                /// x(1) -- The half of the drift volume (0=-x, 1=+x)
                /// f(1) -- The pad flag.  This is 1 if the id is for a pad.
                /// p(5) -- The micro mega (0 to 16)
                /// b(11) -- The pad number (0 to 1727)
                /// \endcode
                namespace Pad {
                    /// @{ The TPC withing the tracker.  0) TPC1 1) TPC2 2) TPC3
                    const GeomIdBit kTPCMSB = Def::TPC::kSeqIdLSB-1;
                    const GeomIdBit kTPCLSB = kTPCMSB-2;
                    const GeomIdMask kTPCMask = MAKE_MASK(kTPCMSB, kTPCLSB);
                    /// @}

                    /// @{ The half of the drift volume.
                    const GeomIdBit kHalfMSB = kTPCLSB-1;
                    const GeomIdBit kHalfLSB = kHalfMSB;
                    const GeomIdMask kHalfMask = MAKE_MASK(kHalfMSB, kHalfLSB);
                    /// @}

                    /// @{ A flag for if this geometry identifier is for a Pad
                    /// within a micro mega.
                    const GeomIdBit kPadFlagMSB = kHalfLSB-1;
                    const GeomIdBit kPadFlagLSB = kPadFlagMSB;
                    const GeomIdMask kPadFlagMask = 
                        MAKE_MASK(kPadFlagMSB,kPadFlagLSB);
                    /// @}

                    /// @{ The micromega within the TPC half.  There are 12
                    /// micromegas in each half.
                    const GeomIdBit kMMegaMSB = kPadFlagLSB-1;
                    const GeomIdBit kMMegaLSB = kMMegaMSB-4;
                    const GeomIdMask kMMegaMask=MAKE_MASK(kMMegaMSB,kMMegaLSB);
                    /// @}

                    /// @{ Define the field to hold the pad number within a
                    /// micromega.
                    const GeomIdBit kPadMSB = kMMegaLSB-1;
                    const GeomIdBit kPadLSB = kPadMSB-10;
                    const GeomIdMask kPadMask = MAKE_MASK(kPadMSB,kPadLSB);
                    /// @}
                };            
            };

            /// Define the FGD specific constants used to decode a geometry
            /// identifier.
            namespace FGD {
                /// Define the sequences required in the FGD.
                enum FGDSeqId {
                    /// A global volume.  This is used for identifiers that
                    /// refer to volumes which contain other geometry
                    /// identifiers.
                    kGlobal = 0,
                    /// A scintillator bar.
                    kScintillator,
                };

                /// The most significant bit of the sequence identifier field.
                /// The sequence id field can have values between 0-15.
                const GeomIdBit kSeqIdMSB = Def::kSubDetectorMSB;
                const GeomIdBit kSeqIdLSB = kSeqIdMSB - 3;
                const GeomIdMask kSeqIdMask = MAKE_MASK(kSeqIdMSB,kSeqIdLSB);

                /// A field that is unique to each global volume.  A global
                /// volume is any volume (with a geometry identifier) that
                /// contains other volumes with geometry identifiers.
                /// Examples are the individual FGDs and the water targets.
                /// The bits are defined as
                ///
                /// \code
                /// gggggggg fffffffffff
                /// g(8)  -- The type of global volume.
                /// f(13) -- The field value.
                /// \endcode
                namespace Global {
                    /// @{ Define a field to hold the type of global volume
                    /// being identified.
                    const GeomIdBit kSeqIdMSB = Def::FGD::kSeqIdLSB-1;
                    const GeomIdBit kSeqIdLSB = kSeqIdMSB-7;
                    const GeomIdMask kSeqIdMask=MAKE_MASK(kSeqIdMSB,kSeqIdLSB);
                    /// @}
                
                    enum GlobalSeqId {
                        /// The two FGD modules.
                        kFGD,
                        /// One of the water targets
                        kTarget,
                        /// A scintillator layer.
                        kLayer,
                    };
                
                    /// @{ The sequence value for this type of global volume.
                    const GeomIdBit kFieldMSB = kSeqIdLSB-1;
                    const GeomIdBit kFieldLSB = 0;
                    const GeomIdMask kFieldMask=MAKE_MASK(kFieldMSB,kFieldLSB);
                    /// @}

                    /// A field definitions for the FGD layers
                    /// \code
                    /// sss x ppppppppp 
                    /// s(3) -- The FGD (FGD1 or FGD2) (0 to 1)
                    /// x(1) -- The type of layer in the module (0=x, 1=y)
                    /// p(9) -- The module within the FGD.
                    /// \endcode
                    namespace Layer {
                        /// @{ The number of the FGD within the detector.  The
                        /// numbering starts at the upstream end and starts
                        /// from zero: 0) FGD1, 1) FGD2.  The FGD2 contains
                        /// the water target.
                        const GeomIdBit kFGDMSB =
                            Def::FGD::Global::kFieldMSB;
                        const GeomIdBit kFGDLSB = kFGDMSB-2;
                        const GeomIdMask kFGDMask = MAKE_MASK(kFGDMSB,
                                                                 kFGDLSB);
                        /// @}
                        
                        /// @{ The layer within the module. Layer zero is X,
                        /// and layer one is Y.
                        const GeomIdBit kLayerMSB = kFGDLSB-1;
                        const GeomIdBit kLayerLSB = kLayerMSB;
                        const GeomIdMask kLayerMask=MAKE_MASK(kLayerMSB,
                                                              kLayerLSB);
                        /// @}
                        
                        /// @{ The module within the the FGD.  The
                        /// numbering starts from zero.  A module consists of
                        /// an X and a Y layer.
                        const GeomIdBit kModuleMSB = kLayerLSB-1;
                        const GeomIdBit kModuleLSB = kModuleMSB-8;
                        const GeomIdMask kModuleMask = MAKE_MASK(kModuleMSB,
                                                                 kModuleLSB);
                        /// @}
                    };            

                };


                /// A field that is unique for each scintillator bar.
                /// \code
                /// sss x pppppp bbbbbbbbbbb
                /// s(3) -- The FGD (FGD1 or FGD2) (0 to 1)
                /// x(1) -- The type of layer in the module (0=x, 1=y)
                /// p(6) -- The module in the  FGD 
                /// b(11) -- The bar number 
                /// \endcode
                namespace Bar {
                    /// @{ The FGD number..  The
                    /// numbering starts at the upstream end and starts from
                    /// zero: 0) FGD1, 1) FGD2 The FGD2 module contains the
                    /// water target.
                    const GeomIdBit kModuleMSB = Def::FGD::kSeqIdLSB-1;
                    const GeomIdBit kModuleLSB = kModuleMSB-2;
                    const GeomIdMask kModuleMask = MAKE_MASK(kModuleMSB,
                                                              kModuleLSB);
                    /// @}

                    /// @{ The layer within the module. Layer zero is X, and
                    /// layer one is Y.
                    const GeomIdBit kLayerMSB = kModuleLSB-1;
                    const GeomIdBit kLayerLSB = kLayerMSB;
                    const GeomIdMask kLayerMask=MAKE_MASK(kLayerMSB,kLayerLSB);
                    /// @}

                    /// @{ The module number within the FGD.  The
                    /// numbering starts from zero.
                    const GeomIdBit kPlaneMSB = kLayerLSB-1;
                    const GeomIdBit kPlaneLSB = kPlaneMSB-5;
                    const GeomIdMask kPlaneMask = MAKE_MASK(kPlaneMSB,
                                                             kPlaneLSB);
                    /// @}

                    /// @{ Define the field to hold the bar number within a
                    /// plane.  
                    const GeomIdBit kBarMSB = kPlaneLSB-1;
                    const GeomIdBit kBarLSB = kBarMSB-10;
                    const GeomIdMask kBarMask = MAKE_MASK(kBarMSB,kBarLSB);
                    /// @}
                };            
            };

            /// Define the ECal specific constants used to decode a geometry
            /// identifier.  The ECal field is 25 bits divided into a
            /// sequence identifier, and a field value.
            ///
            /// \code
            /// ssss mmm fffffffffffffffffff
            /// s(4)  -- The sequence identifier (0 to 15)
            /// m(3)  -- The ecal module number
            /// f(18) -- The field value associated with a sequence id.
            /// \endcode
            ///
            /// Depending on the particular sequence, the field values may be
            /// further sub-divided.
            namespace ECal {
                /// Define the sequences required in the ECal.
                enum ECalSeqId {
                    /// A global volume.  This is used for identifiers that
                    /// refer to volumes which contain other geometry
                    /// identifiers.
                    kGlobal = 0,
                    /// A scintillator bar.
                    kScintillator,
                };

                /// @{The most significant bit of the sequence identifier
                /// field.  The sequence id field can have values between
                /// 0-15.
                const GeomIdBit kSeqIdMSB = Def::kSubDetectorMSB;
                const GeomIdBit kSeqIdLSB = kSeqIdMSB - 3;
                const GeomIdMask kSeqIdMask = MAKE_MASK(kSeqIdMSB,kSeqIdLSB);
                /// @}

                /// Define the module names.
                enum ECalModules {
                    kBottomModule,
                    kSideModule,
                    kTopModule
                };
                const int kNoModule = kBottomModule;

                /// Define the magnet clam names
                enum MagnetClams {
                    kNegXClam,
                    kPosXClam,
                };
                const int kNoClam = kNegXClam;

                /// @{The module id field.  This is always zero for the down
                /// stream ecal.  For the P0D and Tracker ECals, the is 0) -x
                /// bottom 1) +x bottom 2) -x side 3) +x side 4) -x top 5) +x
                /// top
                const GeomIdBit kModuleMSB = kSeqIdLSB-1;
                const GeomIdBit kModuleLSB = kModuleMSB-2;
                const GeomIdMask kModuleMask = MAKE_MASK(kModuleMSB,
                                                         kModuleLSB);
                /// @}

                /// A field that is unique to each global volume.  A global
                /// volume is any volume (with a geometry identifier) that
                /// contains other volumes with geometry identifiers.
                /// Examples are the super-ECalules, and the ECalules.
                /// The bits are defined as
                ///
                /// \code
                /// gggg ffffffffffffff
                /// g(4)  -- The type of global volume.
                /// f(14) -- The field value.
                /// \endcode
                namespace Global {
                    /// @{ Define a field to hold the type of global volume
                    /// being identified.
                    const GeomIdBit kSeqIdMSB = Def::ECal::kModuleLSB-1;
                    const GeomIdBit kSeqIdLSB = kSeqIdMSB-3;
                    const GeomIdMask kSeqIdMask=MAKE_MASK(kSeqIdMSB,kSeqIdLSB);
                    /// @}
                
                    enum GlobalSeqId {
                        /// A special case for one of a kind global volumes
                        kECal,
                        /// One of the ECal scintillator layers.
                        kLayer,
                        /// One of the Radiators
                        kRadiator,
                        /// A special case for one of a kind container volumes used to reposition the P0D
                        /// and barrel ECal modules. In the geometry, modules are eg.
                        /// .../BrlECal_0/Top_0/...
                        /// BrlECal_0 is the kContainer, Top_0 is the kECal
                        kContainer,
                    };
                
                    /// @{ The sequence value for this type of global volume.
                    const GeomIdBit kFieldMSB = kSeqIdLSB-1;
                    const GeomIdBit kFieldLSB = 0;
                    const GeomIdMask kFieldMask=MAKE_MASK(kFieldMSB,kFieldLSB);
                    /// @}
                };

                /// A field that is unique for each scintillator bar.
                ///
                /// \code
                /// pppppp bbbbbbbbbbb
                /// p(6) -- The layer in the ECal
                /// b(12) -- The bar number 
                /// \endcode
                namespace Bar {
                    /// @{ The layer within the ECal module.  Layer numbering
                    /// starts from zero.
                    const GeomIdBit kLayerMSB = Def::ECal::kModuleLSB-1;
                    const GeomIdBit kLayerLSB = kLayerMSB-5;
                    const GeomIdMask kLayerMask = MAKE_MASK(kLayerMSB,
                                                            kLayerLSB);
                    /// @}

                    /// @{ Define the field to hold the bar number within a
                    /// layer.
                    const GeomIdBit kBarMSB = kLayerLSB-1;
                    const GeomIdBit kBarLSB = kBarMSB-11;
                    const GeomIdMask kBarMask = MAKE_MASK(kBarMSB,kBarLSB);
                    /// @}
                };            
            };

            /// Define the SMRD specific constants used to decode a geometry
            /// identifier.  The SMRD field is 25 bits divided into a sequence
            /// identifier, and a field value.
            ///
            /// \code
            /// sssss ffffffffffffffffffff
            /// s(4)  -- The sequence identifier (0 to 15)
            /// f(21) -- The field value associated with a sequence id.
            /// \endcode
            ///
            /// Depending on the particular sequence, the field values may be
            /// further sub-divided.
            namespace SMRD {
                /// Define the sequences required in the SRMD.
                enum SRMDSeqId {
                    /// A global volume.  This is used for identifiers that
                    /// refer to volumes which contain other geometry
                    /// identifiers.
                    kGlobal = 0,
                    /// A scintillator bar.
                    kScintillator,
                };

                /// The most significant bit of the sequence identifier field.
                /// The sequence id field can have values between 0-15.
                const GeomIdBit kSeqIdMSB = Def::kSubDetectorMSB;
                const GeomIdBit kSeqIdLSB = kSeqIdMSB - 3;
                const GeomIdMask kSeqIdMask = MAKE_MASK(kSeqIdMSB,kSeqIdLSB);

                /// A field that is unique to each global volume.  A global
                /// volume is any volume (with a geometry identifier) that
                /// contains other volumes with geometry identifiers.
                /// Examples are the SMRD modules.  The bits are defined as
                ///
                /// \code
                /// gggggggg fffffffffff
                /// g(8)  -- The type of global volume.
                /// f(13) -- The field value.
                /// \endcode
                namespace Global {
                    /// @{ Define a field to hold the type of global volume
                    /// being identified.
                    const GeomIdBit kSeqIdMSB = Def::SMRD::kSeqIdLSB-1;
                    const GeomIdBit kSeqIdLSB = kSeqIdMSB-7;
                    const GeomIdMask kSeqIdMask=MAKE_MASK(kSeqIdMSB,kSeqIdLSB);
                    /// @}
                
                    enum GlobalSeqId {
                        /// The sequence for all of the modules in the SMRD.
                        kModule = 1,
                    };
                
                    /// @{ The sequence value for this type of global volume.
                    const GeomIdBit kFieldMSB = kSeqIdLSB-1;
                    const GeomIdBit kFieldLSB = 0;
                    const GeomIdMask kFieldMask=MAKE_MASK(kFieldMSB,kFieldLSB);
                    /// @}

                    /// A field definitions for the SMRD modules
                    /// \code
                    /// c yyyy mmmm ssss
                    /// c(1) -- The magnet clam (0 left, 1 right).
                    /// y(4) -- The yoke in the magnet (0 to 7)
                    /// m(4) -- The layer in the magnet. (0 to 15)
                    /// s(4) -- The slot in the layer (0 to 7)
                    /// \endcode
                    namespace Module {
                        /// @{The clam within the magnet.  0) Left Clam
                        /// (positive X), 1) Right clam (negative X).
                        const GeomIdBit kClamMSB = 
                            Def::SMRD::Global::kFieldMSB;
                        const GeomIdBit kClamLSB = kClamMSB;
                        const GeomIdMask kClamMask = MAKE_MASK(kClamMSB,
                                                               kClamLSB);
                        /// @}

                        /// @{ The yoke of the particular clam.  The numbering
                        /// starts on the upstream end.
                        const GeomIdBit kYokeMSB = kClamLSB-1;
                        const GeomIdBit kYokeLSB = kYokeMSB-3;
                        const GeomIdMask kYokeMask=MAKE_MASK(kYokeMSB,kYokeLSB);
                        /// @}

                        /// @{ The layer within a yoke.  The numbering starts
                        /// at the inner most side of the yoke.
                        const GeomIdBit kLayerMSB = kYokeLSB-1;
                        const GeomIdBit kLayerLSB = kLayerMSB-3;
                        const GeomIdMask kLayerMask = MAKE_MASK(kLayerMSB,
                                                                kLayerLSB);
                        /// @}


                        /// @{ The slot within a layer.
                        const GeomIdBit kSlotMSB = kLayerLSB-1;
                        const GeomIdBit kSlotLSB = kSlotMSB-3;
                        const GeomIdMask kSlotMask = MAKE_MASK(kSlotMSB,
                                                               kSlotLSB);
                        /// @}
                    };            
                };

                /// A field that is unique for each scintillator bar.
                /// \code
                /// c yyyy mmmm ssss bbbbbbbb
                /// c(1) -- The magnet clam (0 left, 1 right).
                /// y(4) -- The yoke in the magnet (0 to 7)
                /// m(4) -- The layer in the magnet. (0 to 15)
                /// s(4) -- The slot in the layer (0 to 7)
                /// b(8) -- The bar number in the module
                /// \endcode
                namespace Bar {
                    /// @{The clam within the magnet.  0) Left Clam (positive
                    /// X), 1) Right clam (negative X).
                    const GeomIdBit kClamMSB = Def::SMRD::kSeqIdLSB-1;
                    const GeomIdBit kClamLSB = kClamMSB;
                    const GeomIdMask kClamMask = MAKE_MASK(kClamMSB,kClamLSB);
                    /// @}

                    /// @{ The yoke of the particular clam.  The numbering
                    /// starts on the upstream end.
                    const GeomIdBit kYokeMSB = kClamLSB-1;
                    const GeomIdBit kYokeLSB = kYokeMSB-3;
                    const GeomIdMask kYokeMask=MAKE_MASK(kYokeMSB,kYokeLSB);
                    /// @}

                    /// @{ The layer within a yoke.  The numbering starts at
                    /// the inner most side of the yoke.
                    const GeomIdBit kLayerMSB = kYokeLSB-1;
                    const GeomIdBit kLayerLSB = kLayerMSB-3;
                    const GeomIdMask kLayerMask = MAKE_MASK(kLayerMSB,
                                                            kLayerLSB);
                    /// @}


                    /// @{ The slot within a layer.
                    const GeomIdBit kSlotMSB = kLayerLSB-1;
                    const GeomIdBit kSlotLSB = kSlotMSB-3;
                    const GeomIdMask kSlotMask = MAKE_MASK(kSlotMSB,kSlotLSB);
                    /// @}

                    /// @{ Define the field to hold the bar number within a
                    /// slot.
                    const GeomIdBit kBarMSB = kSlotLSB-1;
                    const GeomIdBit kBarLSB = kBarMSB-7;
                    const GeomIdMask kBarMask = MAKE_MASK(kBarMSB,kBarLSB);
                    /// @}
                };            
            };

            /// Define the INGRID specific constants used to decode a geometry
            /// identifier. The Ingrid field is 25 bits divided into an
            /// identifier the numbering of module, tracker and scintillator
            /// and a flag that indicates in which projection is the
            /// scintillator plane.
            ///
            /// \code
            /// ii mmmmmmmm ttttttt p sssssss
            /// i(2) [23:24] -- Identifies the object type: Veto/Module.
            /// m(8) [15:22] -- Number of the module/veto plane.
            /// t(7) [ 8:14] -- Identifies the tracker on the module.

            /// p(1) [ 7: 7] -- Projection of the scintillator: Hori./Vert/

            /// s(7) [ 0: 6] -- Identifies scintillator in the plane/tracker.
            /// \endcode
            ///
            /// On the case of the Veto planes the tracker number is always
            /// the same (there is no concept of trackers on the vetos).
            namespace INGRID {
                /// Define the identifiers for the object
                enum INGRIDObjID {
                    /// A module.
                    kIngridModule = 0,
                    /// A veto plane.
                    kIngridVeto,
                };

                /// The most significant bit of the object identifier field.
                /// The object identifier can have values between 0-3.
                const GeomIdBit  kIngridObjIDMSB  = Def::kSubDetectorMSB;
                const GeomIdBit  kIngridObjIDLSB  = kIngridObjIDMSB - 1;
                const GeomIdMask kIngridObjIDMask = MAKE_MASK(kIngridObjIDMSB,
                                                              kIngridObjIDLSB);

                /// The most significant bit of module number field.
                /// The module number can have values between 0-255.
                const GeomIdBit  kIngridModNumMSB  = kIngridObjIDLSB - 1;
                const GeomIdBit  kIngridModNumLSB  = kIngridModNumMSB - 7;
                const GeomIdMask kIngridModNumMask =MAKE_MASK(kIngridModNumMSB,
                                                              kIngridModNumLSB);

                /// The most significant bit of tracker number field.
                /// The tracker number can have values between 0-127.
                const GeomIdBit  kIngridTrkNumMSB  = kIngridModNumLSB - 1;
                const GeomIdBit  kIngridTrkNumLSB  = kIngridTrkNumMSB - 6;
                const GeomIdMask kIngridTrkNumMask =MAKE_MASK(kIngridTrkNumMSB,
                                                              kIngridTrkNumLSB);

                /// Define the scintillators directions
                enum IngridScintillatorDirectionID{
                        /// Vertical scintillator.
                        kVertical = 0,
                        /// Horizontal scintillator.
                        kHorizontal,
                };

                /// The most significant bit of projection field.
                /// The projection can have values between 0-1.
                const GeomIdBit  kIngridProjMSB  = kIngridTrkNumLSB - 1;
                const GeomIdBit  kIngridProjLSB  = kIngridProjMSB;
                const GeomIdMask kIngridProjMask = MAKE_MASK(kIngridProjMSB,
                                                             kIngridProjLSB);

                /// The most significant bit of scintillator number field.
                /// The scintillator number can have values between 0-127.
                const GeomIdBit  kIngridSciNumMSB  = kIngridProjLSB - 1;
                const GeomIdBit  kIngridSciNumLSB  = kIngridSciNumMSB - 6;
                const GeomIdMask kIngridSciNumMask =MAKE_MASK(kIngridSciNumMSB,
                                                              kIngridSciNumLSB);
            };
#undef MAKE_FIELD_MASK
        };
    };
};
#endif
