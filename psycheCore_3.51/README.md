### psycheCore

Author: Anselmo Cervera, Alexander Izmaylov and Mark Scott

### Description

The core package of the psyche interface.

### Introduction

psycheCore, as the name suggests, holds the core methods and class definitions of the psyche interface.  One of the critical requirements of the psyche interface is that it uses as little memory per event as possible and that it can process events as quickly as possible.  This is needed for the BANFF and MaCh3 fitters, since they have to fit the data in a reasonable amount of time.  As such most classes store information as floats rather than doubles, arrays rather than std::vectors and use bitfields for geometry information.  All data classes are created when loading in the events with your InputConverter, then wherever possible pointers to these objects are copied between the different objects that need to access them.

The major classes and methods of interest to analysers are described below:

### Base Data Classes

The BaseDataClasses define all of the data objects needed to fit the near detector data.  These classes should be as generic as possible, though since we have only had ND280 tracker analyses to use during the construction of psyche this might not be the case- please feel free to contact the package managers if you want to add or modify classes to handle your event selection. Starting at the highest level and working down to the lowest, below are some of the coommonly used classes:

-AnaSuperEventB- This contains pointers to the raw AnaEventB (RawEvent) and a version of that event with systematic variations applied (Event).  It also contains the Data/MC POT ratio for that event if you are using the Experiment class as done in the RunExpPreloadExample.cxx

-AnaEventB- This class contains all of the truth and reconstructed information of a psyche event.  An event here is defined as a reconstructed neutrino interaction candidate with the associated truth information needed to perform cross section and flux reweighting.  It also contains the ND280 data quality information (AnaDataQualityB), the beam data quality (AnaBeamB), the event information (AnaEventInfoB) and the event summary information and systematics box.

-AnaVertexB- A class defining a reconstructed vertex

-AnaTrackB- A class defining reconstructed track-like objects
-AnaSubTrackB- This class defines information about the subtracks that form the main AnaTrackB

-AnaShowerB- Does not currently exist, but will hold information for shower-like objects
-AnaSubShowerB- Does not currently exist, but will hold information for constituents of shower-like objects

-AnaFgdTimeBinB- The FGD time bin information used in Michel cuts and systematics

-AnaTrueTrackB- A class holding the truth trajectory information

-AnaTrueVertexB- A class holding the truth vertex information and providing a link to the associated RooTrackerVtx 

-SystBoxB- A class holding pointers to all the information needed to apply detector systematics to the event

-AnaEventSummaryB- The primary class used to hold summary information about the event 

psyche also defines detector specific versions of the AnaSubTrackB and (soon) AnaSubShowerB classes, which hold information required for selections using information from that specific detector.  As an example, the AnaTpcTrackB contains TPC dE/dx measurements and momentum refits.

Each reconstructed object also has a pointer called 'Original'.  When creating each super event, psyche clones all of the information in the RawEvent to create the Event ready for systematic variations.  When doing this the Original pointer is set to the corresponding object in the RawEvent, so that a link is maintained. 

### The Event Summary

When a selection is applied to an event in psyche it fills the AnaEventSummaryB class associated to that event.  This class stores pointers to the selected reconstructed objects and associated truth vertices in arrays, with each entry in the array corresponding to a possible sample, as defined in nd280Samples.  This allows multiple event selections to be run on the same event and allows analysers to retrieve the event information regardless of whether the event was selected or not.  This is done in the AnalysisManager::ProcessEvent method, for example, to get the true vertex associated with a selection:

```
    event.Summary->TrueVertex[selection.GetSampleEnum()]
```

The event summary also contains the EventSample data member, which stores the nd280Samples::SampleEnum corresponding to the selection the event passed.  This is set to kUnassigned (0) if no event selection was passed.

### The nd280Samples Class

This class defines an enumeration, with an entry for each selection in psyche, that is used to identify and separate each selection being applied to the events.  If you are adding a new selection to psyche make sure you update this class with an additional sample enumerator.



