#ifndef DrawingUtils_h
#define DrawingUtils_h

#include <map>
#include <vector>
#include <stdio.h>
#include <iostream>
#include <TTree.h>
#include <TH1F.h>
#include <TH1D.h>
#include <TH2F.h>
#include <TH2D.h>
#include <TLegend.h>
#include <TGraphAsymmErrors.h>

#include "Experiment.hxx"



typedef TH1D TH1_h;
typedef TH2D TH2_h;

/// This namespace contains a set of general utilities for drawing
namespace drawUtils {


  enum OptionEnum{
    kNOERROR=0,
    kAREA    
  };

  /// Convert a string to upper-case, so we can do case-insensitive comparisons when parsing
  /// the "opt" parameter, for example.
  std::string ToUpper(const std::string& str);

  /// convert integer to string
  std::string GetString(int code);

  /// convert double to string
  std::string GetString(double code);

  /// Check wether the tree has a given variable
  bool TreeHasVar(TTree* tree, const std::string& var);

  ///Get the Value of an integer variable from the tree
  int GetVarFromTree(TTree* tree, const std::string& var);

  /// get the number of weights in the tree
  int GetNWeights(TTree* tree);

  /// get the number of weights in the tree
  int GetNToys(TTree* tree);

  /// get the reference toy in the tree
  int GetRefToy(TTree* tree);

  ///Get the Value of an integer variable from the experiment
  int GetVarFromExperiment(const std::string& var, Experiment& exp,  const std::string& groupName="all", const std::string& mcSampleName="all");
  
  /// Normalize bin contents by bin width. return the with of the bin with minimum width
  void NormalizeVariableBinning(TH1* h, int mode, const std::string& opt, Double_t& minwidth);

  /// Normalize bin contents by bin width. 
  void NormalizeVariableBinning(TH1* h, int mode, const std::string& opt);

  /// Check if specific option exists, and if so if it appears in option field
  bool CheckOption(const std::string& uopt, const std::string& this_opt);

  /// Same as previous using enum instead of string
  bool CheckOption(const std::string& uopt, OptionEnum this_opt);

  /// Check if specific option appears in option field (don't check if it exists: Added with AddOption)
  bool CheckInternalOption(const std::string& uopt, const std::string& this_opt);

  /// convert enum option to string
  std::string ConvertOption(OptionEnum this_opt);

  /// Explain a given option given as enum
  void ExplainOption(OptionEnum opt);

  /// Explain a given option 
  void ExplainOption(const std::string& opt);

  /// Check if the option is in the list of available options (added with AddOption)
  bool IsValidOption(const std::string& opt);

  /// Check if the input string contails only valid options
  bool ContainValidOptions(const std::string& uopt);

  /// Add option as valid, provided name and exlaination
  void AddOption(const std::string& opt, const std::string& info);

  /// Build the map of valid options with AddOption
  void BuildOptions();

  /// List sll valid options and a description of each of them
  void ListOptions();

  /// Add an entry to the Legend and resize it
  void AddLegendEntry(TLegend* leg, TObject* ht, const std::string&type, const std::string& opt);

  /// Get automatically the title for the Y axis
  std::string GetAutoTitleY(TH1* h, const std::string& titleX);
  
  extern double legendEntryHeight;

  void FindAndReplaceAll(std::string& data, const std::string& toSearch, const std::string& replaceStr);

  /// Validate a histogram,  return a vector of bins with non-valid entries
  bool ValidateHistogramBinValues(const TH1_h& h, std::vector<Int_t>& bins);

  /// Validate a histogram,  return a double vector of bins - with
  /// valid/non-valid boolean numbers, individual vectors, and also counters for bad bins in x and y
  bool ValidateHistogramBinValues(const TH2_h& h, std::vector<std::vector<bool> >& bins, 
      std::vector<bool>& bins_x, std::vector<bool>& bins_y);
  
}

#endif


