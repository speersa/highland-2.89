//
// File generated by /t2k/Software/v12r25/ROOT/v5r34p34n00/Linux-x86_64//bin/rootcint at Thu Apr 20 02:09:33 2023

// Do NOT change. Changes will be lost next time file is generated
//

#define R__DICTIONARY_FILENAME dIhomedIt2kdIaspeersdIHighland_InstallsdIHighLAND_2dO89dIpsycheND280Utils_3dO73dILinuxmICentOS_7mIgcc_4dO8mIx86_64dIdictdIG_DetectorDefinition
#include "RConfig.h" //rootcint 4834
#if !defined(R__ACCESS_IN_SYMBOL)
//Break the privacy of classes -- Disabled for the moment
#define private public
#define protected public
#endif

// Since CINT ignores the std namespace, we need to do so in this file.
namespace std {} using namespace std;
#include "G_DetectorDefinition.h"

#include "TClass.h"
#include "TBuffer.h"
#include "TMemberInspector.h"
#include "TInterpreter.h"
#include "TVirtualMutex.h"
#include "TError.h"

#ifndef G__ROOT
#define G__ROOT
#endif

#include "RtypesImp.h"
#include "TIsAProxy.h"
#include "TFileMergeInfo.h"

// Direct notice to TROOT of the dictionary's loading.
namespace {
   static struct DictInit {
      DictInit() {
         ROOT::RegisterModule();
      }
   } __TheDictionaryInitializer;
}

// START OF SHADOWS

namespace ROOTShadow {
   namespace Shadow {
   } // of namespace Shadow
} // of namespace ROOTShadow
// END OF SHADOWS

namespace DetDef {
   namespace ROOTDict {
      inline ::ROOT::TGenericClassInfo *GenerateInitInstance();
      static void DetDef_Dictionary();

      // Function generating the singleton type initializer
      inline ::ROOT::TGenericClassInfo *GenerateInitInstance()
      {
         static ::ROOT::TGenericClassInfo 
            instance("DetDef", 0 /*version*/, "/home/t2k/aspeers/Highland_Installs/HighLAND_2.89/psycheND280Utils_3.73/inc/DetectorDefinition.hxx", 10,
                     ::ROOT::DefineBehavior((void*)0,(void*)0),
                     &DetDef_Dictionary, 0);
         return &instance;
      }
      // Insure that the inline function is _not_ optimized away by the compiler
      ::ROOT::TGenericClassInfo *(*_R__UNIQUE_(InitFunctionKeeper))() = &GenerateInitInstance;  
      // Static variable to force the class initialization
      static ::ROOT::TGenericClassInfo *_R__UNIQUE_(Init) = GenerateInitInstance(); R__UseDummy(_R__UNIQUE_(Init));

      // Dictionary for non-ClassDef classes
      static void DetDef_Dictionary() {
         GenerateInitInstance()->GetClass();
      }

   }
}

/********************************************************
* /home/t2k/aspeers/Highland_Installs/HighLAND_2.89/psycheND280Utils_3.73/Linux-CentOS_7-gcc_4.8-x86_64/dict/G_DetectorDefinition.cxx
* CAUTION: DON'T CHANGE THIS FILE. THIS FILE IS AUTOMATICALLY GENERATED
*          FROM HEADER FILES LISTED IN G__setup_cpp_environmentXXX().
*          CHANGE THOSE HEADER FILES AND REGENERATE THIS FILE.
********************************************************/

#ifdef G__MEMTEST
#undef malloc
#undef free
#endif

#if defined(__GNUC__) && __GNUC__ >= 4 && ((__GNUC_MINOR__ == 2 && __GNUC_PATCHLEVEL__ >= 1) || (__GNUC_MINOR__ >= 3))
#pragma GCC diagnostic ignored "-Wstrict-aliasing"
#endif

extern "C" void G__cpp_reset_tagtableG_DetectorDefinition();

extern "C" void G__set_cpp_environmentG_DetectorDefinition() {
  G__cpp_reset_tagtableG_DetectorDefinition();
}
#include <new>
extern "C" int G__cpp_dllrevG_DetectorDefinition() { return(30051515); }

/*********************************************************
* Member function Interface Method
*********************************************************/

/* DetDef */
static int G__G_DetectorDefinition_221_0_1(G__value* result7, G__CONST char* funcname, struct G__param* libp, int hash)
{
      DetDef::DumpVolumes();
      G__setnull(result7);
   return(1 || funcname || hash || result7 || libp) ;
}

static int G__G_DetectorDefinition_221_0_2(G__value* result7, G__CONST char* funcname, struct G__param* libp, int hash)
{
      DetDef::DumpFGDInfo();
      G__setnull(result7);
   return(1 || funcname || hash || result7 || libp) ;
}


/* Setting up global function */

/*********************************************************
* Member function Stub
*********************************************************/

/* DetDef */

/*********************************************************
* Global function Stub
*********************************************************/

/*********************************************************
* Get size of pointer to member function
*********************************************************/
class G__Sizep2memfuncG_DetectorDefinition {
 public:
  G__Sizep2memfuncG_DetectorDefinition(): p(&G__Sizep2memfuncG_DetectorDefinition::sizep2memfunc) {}
    size_t sizep2memfunc() { return(sizeof(p)); }
  private:
    size_t (G__Sizep2memfuncG_DetectorDefinition::*p)();
};

size_t G__get_sizep2memfuncG_DetectorDefinition()
{
  G__Sizep2memfuncG_DetectorDefinition a;
  G__setsizep2memfunc((int)a.sizep2memfunc());
  return((size_t)a.sizep2memfunc());
}


/*********************************************************
* virtual base class offset calculation interface
*********************************************************/

   /* Setting up class inheritance */

/*********************************************************
* Inheritance information setup/
*********************************************************/
extern "C" void G__cpp_setup_inheritanceG_DetectorDefinition() {

   /* Setting up class inheritance */
}

/*********************************************************
* typedef information setup/
*********************************************************/
extern "C" void G__cpp_setup_typetableG_DetectorDefinition() {

   /* Setting up typedef entry */
   G__search_typename2("vector<ROOT::TSchemaHelper>",117,G__get_linked_tagnum(&G__G_DetectorDefinitionLN_vectorlEROOTcLcLTSchemaHelpercOallocatorlEROOTcLcLTSchemaHelpergRsPgR),0,-1);
   G__setnewtype(-1,NULL,0);
   G__search_typename2("reverse_iterator<const_iterator>",117,G__get_linked_tagnum(&G__G_DetectorDefinitionLN_reverse_iteratorlEvectorlEROOTcLcLTSchemaHelpercOallocatorlEROOTcLcLTSchemaHelpergRsPgRcLcLiteratorgR),0,G__get_linked_tagnum(&G__G_DetectorDefinitionLN_vectorlEROOTcLcLTSchemaHelpercOallocatorlEROOTcLcLTSchemaHelpergRsPgR));
   G__setnewtype(-1,NULL,0);
   G__search_typename2("reverse_iterator<iterator>",117,G__get_linked_tagnum(&G__G_DetectorDefinitionLN_reverse_iteratorlEvectorlEROOTcLcLTSchemaHelpercOallocatorlEROOTcLcLTSchemaHelpergRsPgRcLcLiteratorgR),0,G__get_linked_tagnum(&G__G_DetectorDefinitionLN_vectorlEROOTcLcLTSchemaHelpercOallocatorlEROOTcLcLTSchemaHelpergRsPgR));
   G__setnewtype(-1,NULL,0);
   G__search_typename2("vector<TVirtualArray*>",117,G__get_linked_tagnum(&G__G_DetectorDefinitionLN_vectorlETVirtualArraymUcOallocatorlETVirtualArraymUgRsPgR),0,-1);
   G__setnewtype(-1,NULL,0);
   G__search_typename2("reverse_iterator<const_iterator>",117,G__get_linked_tagnum(&G__G_DetectorDefinitionLN_reverse_iteratorlEvectorlETVirtualArraymUcOallocatorlETVirtualArraymUgRsPgRcLcLiteratorgR),0,G__get_linked_tagnum(&G__G_DetectorDefinitionLN_vectorlETVirtualArraymUcOallocatorlETVirtualArraymUgRsPgR));
   G__setnewtype(-1,NULL,0);
   G__search_typename2("reverse_iterator<iterator>",117,G__get_linked_tagnum(&G__G_DetectorDefinitionLN_reverse_iteratorlEvectorlETVirtualArraymUcOallocatorlETVirtualArraymUgRsPgRcLcLiteratorgR),0,G__get_linked_tagnum(&G__G_DetectorDefinitionLN_vectorlETVirtualArraymUcOallocatorlETVirtualArraymUgRsPgR));
   G__setnewtype(-1,NULL,0);
   G__search_typename2("TMatrixTBase<Float_t>",117,G__get_linked_tagnum(&G__G_DetectorDefinitionLN_TMatrixTBaselEfloatgR),0,-1);
   G__setnewtype(-1,NULL,0);
   G__search_typename2("TMatrixTBase<Double_t>",117,G__get_linked_tagnum(&G__G_DetectorDefinitionLN_TMatrixTBaselEdoublegR),0,-1);
   G__setnewtype(-1,NULL,0);
   G__search_typename2("TVectorT<Float_t>",117,G__get_linked_tagnum(&G__G_DetectorDefinitionLN_TVectorTlEfloatgR),0,-1);
   G__setnewtype(-1,NULL,0);
   G__search_typename2("TVectorT<Double_t>",117,G__get_linked_tagnum(&G__G_DetectorDefinitionLN_TVectorTlEdoublegR),0,-1);
   G__setnewtype(-1,NULL,0);
   G__search_typename2("TMatrixT<Float_t>",117,G__get_linked_tagnum(&G__G_DetectorDefinitionLN_TMatrixTlEfloatgR),0,-1);
   G__setnewtype(-1,NULL,0);
   G__search_typename2("TMatrixTRow_const<Float_t>",117,G__get_linked_tagnum(&G__G_DetectorDefinitionLN_TMatrixTRow_constlEfloatgR),0,-1);
   G__setnewtype(-1,NULL,0);
   G__search_typename2("TMatrixTColumn_const<Float_t>",117,G__get_linked_tagnum(&G__G_DetectorDefinitionLN_TMatrixTColumn_constlEfloatgR),0,-1);
   G__setnewtype(-1,NULL,0);
   G__search_typename2("TMatrixTDiag_const<Float_t>",117,G__get_linked_tagnum(&G__G_DetectorDefinitionLN_TMatrixTDiag_constlEfloatgR),0,-1);
   G__setnewtype(-1,NULL,0);
   G__search_typename2("TMatrixTFlat_const<Float_t>",117,G__get_linked_tagnum(&G__G_DetectorDefinitionLN_TMatrixTFlat_constlEfloatgR),0,-1);
   G__setnewtype(-1,NULL,0);
   G__search_typename2("TMatrixTSub_const<Float_t>",117,G__get_linked_tagnum(&G__G_DetectorDefinitionLN_TMatrixTSub_constlEfloatgR),0,-1);
   G__setnewtype(-1,NULL,0);
   G__search_typename2("TMatrixTSparseRow_const<Float_t>",117,G__get_linked_tagnum(&G__G_DetectorDefinitionLN_TMatrixTSparseRow_constlEfloatgR),0,-1);
   G__setnewtype(-1,NULL,0);
   G__search_typename2("TMatrixTSparseDiag_const<Float_t>",117,G__get_linked_tagnum(&G__G_DetectorDefinitionLN_TMatrixTSparseDiag_constlEfloatgR),0,-1);
   G__setnewtype(-1,NULL,0);
   G__search_typename2("TMatrixTRow<Float_t>",117,G__get_linked_tagnum(&G__G_DetectorDefinitionLN_TMatrixTRowlEfloatgR),0,-1);
   G__setnewtype(-1,NULL,0);
   G__search_typename2("TMatrixTColumn<Float_t>",117,G__get_linked_tagnum(&G__G_DetectorDefinitionLN_TMatrixTColumnlEfloatgR),0,-1);
   G__setnewtype(-1,NULL,0);
   G__search_typename2("TMatrixTDiag<Float_t>",117,G__get_linked_tagnum(&G__G_DetectorDefinitionLN_TMatrixTDiaglEfloatgR),0,-1);
   G__setnewtype(-1,NULL,0);
   G__search_typename2("TMatrixTFlat<Float_t>",117,G__get_linked_tagnum(&G__G_DetectorDefinitionLN_TMatrixTFlatlEfloatgR),0,-1);
   G__setnewtype(-1,NULL,0);
   G__search_typename2("TMatrixTSub<Float_t>",117,G__get_linked_tagnum(&G__G_DetectorDefinitionLN_TMatrixTSublEfloatgR),0,-1);
   G__setnewtype(-1,NULL,0);
   G__search_typename2("TMatrixTSparseRow<Float_t>",117,G__get_linked_tagnum(&G__G_DetectorDefinitionLN_TMatrixTSparseRowlEfloatgR),0,-1);
   G__setnewtype(-1,NULL,0);
   G__search_typename2("TMatrixTSparseDiag<Float_t>",117,G__get_linked_tagnum(&G__G_DetectorDefinitionLN_TMatrixTSparseDiaglEfloatgR),0,-1);
   G__setnewtype(-1,NULL,0);
   G__search_typename2("TElementActionT<Float_t>",117,G__get_linked_tagnum(&G__G_DetectorDefinitionLN_TElementActionTlEfloatgR),0,-1);
   G__setnewtype(-1,NULL,0);
   G__search_typename2("TElementPosActionT<Float_t>",117,G__get_linked_tagnum(&G__G_DetectorDefinitionLN_TElementPosActionTlEfloatgR),0,-1);
   G__setnewtype(-1,NULL,0);
}

/*********************************************************
* Data Member information setup/
*********************************************************/

   /* Setting up class,struct,union tag member variable */

   /* DetDef */
static void G__setup_memvarDetDef(void) {
   G__tag_memvar_setup(G__get_linked_tagnum(&G__G_DetectorDefinitionLN_DetDef));
   {
   G__memvar_setup((void*)(&DetDef::fgd1min),102,0,0,-1,G__defined_typename("Float_t"),-1,1,"fgd1min[3]=",0,(char*)NULL);
   G__memvar_setup((void*)(&DetDef::fgd1max),102,0,0,-1,G__defined_typename("Float_t"),-1,1,"fgd1max[3]=",0,(char*)NULL);
   G__memvar_setup((void*)(&DetDef::fgd2min),102,0,0,-1,G__defined_typename("Float_t"),-1,1,"fgd2min[3]=",0,(char*)NULL);
   G__memvar_setup((void*)(&DetDef::fgd2max),102,0,0,-1,G__defined_typename("Float_t"),-1,1,"fgd2max[3]=",0,(char*)NULL);
   G__memvar_setup((void*)(&DetDef::p0dmin),102,0,0,-1,G__defined_typename("Float_t"),-1,1,"p0dmin[3]=",0,(char*)NULL);
   G__memvar_setup((void*)(&DetDef::p0dmax),102,0,0,-1,G__defined_typename("Float_t"),-1,1,"p0dmax[3]=",0,(char*)NULL);
   G__memvar_setup((void*)(&DetDef::dsecalmin),102,0,0,-1,G__defined_typename("Float_t"),-1,1,"dsecalmin[3]=",0,(char*)NULL);
   G__memvar_setup((void*)(&DetDef::dsecalmax),102,0,0,-1,G__defined_typename("Float_t"),-1,1,"dsecalmax[3]=",0,(char*)NULL);
   G__memvar_setup((void*)(&DetDef::tecalLmin),102,0,0,-1,G__defined_typename("Float_t"),-1,1,"tecalLmin[3]=",0,(char*)NULL);
   G__memvar_setup((void*)(&DetDef::tecalLmax),102,0,0,-1,G__defined_typename("Float_t"),-1,1,"tecalLmax[3]=",0,(char*)NULL);
   G__memvar_setup((void*)(&DetDef::tecalRmin),102,0,0,-1,G__defined_typename("Float_t"),-1,1,"tecalRmin[3]=",0,(char*)NULL);
   G__memvar_setup((void*)(&DetDef::tecalRmax),102,0,0,-1,G__defined_typename("Float_t"),-1,1,"tecalRmax[3]=",0,(char*)NULL);
   G__memvar_setup((void*)(&DetDef::tecalTLmin),102,0,0,-1,G__defined_typename("Float_t"),-1,1,"tecalTLmin[3]=",0,(char*)NULL);
   G__memvar_setup((void*)(&DetDef::tecalTLmax),102,0,0,-1,G__defined_typename("Float_t"),-1,1,"tecalTLmax[3]=",0,(char*)NULL);
   G__memvar_setup((void*)(&DetDef::tecalTRmin),102,0,0,-1,G__defined_typename("Float_t"),-1,1,"tecalTRmin[3]=",0,(char*)NULL);
   G__memvar_setup((void*)(&DetDef::tecalTRmax),102,0,0,-1,G__defined_typename("Float_t"),-1,1,"tecalTRmax[3]=",0,(char*)NULL);
   G__memvar_setup((void*)(&DetDef::tecalBLmin),102,0,0,-1,G__defined_typename("Float_t"),-1,1,"tecalBLmin[3]=",0,(char*)NULL);
   G__memvar_setup((void*)(&DetDef::tecalBLmax),102,0,0,-1,G__defined_typename("Float_t"),-1,1,"tecalBLmax[3]=",0,(char*)NULL);
   G__memvar_setup((void*)(&DetDef::tecalBRmin),102,0,0,-1,G__defined_typename("Float_t"),-1,1,"tecalBRmin[3]=",0,(char*)NULL);
   G__memvar_setup((void*)(&DetDef::tecalBRmax),102,0,0,-1,G__defined_typename("Float_t"),-1,1,"tecalBRmax[3]=",0,(char*)NULL);
   G__memvar_setup((void*)(&DetDef::pecalLmin),102,0,0,-1,G__defined_typename("Float_t"),-1,1,"pecalLmin[3]=",0,(char*)NULL);
   G__memvar_setup((void*)(&DetDef::pecalLmax),102,0,0,-1,G__defined_typename("Float_t"),-1,1,"pecalLmax[3]=",0,(char*)NULL);
   G__memvar_setup((void*)(&DetDef::pecalRmin),102,0,0,-1,G__defined_typename("Float_t"),-1,1,"pecalRmin[3]=",0,(char*)NULL);
   G__memvar_setup((void*)(&DetDef::pecalRmax),102,0,0,-1,G__defined_typename("Float_t"),-1,1,"pecalRmax[3]=",0,(char*)NULL);
   G__memvar_setup((void*)(&DetDef::pecalTLmin),102,0,0,-1,G__defined_typename("Float_t"),-1,1,"pecalTLmin[3]=",0,(char*)NULL);
   G__memvar_setup((void*)(&DetDef::pecalTLmax),102,0,0,-1,G__defined_typename("Float_t"),-1,1,"pecalTLmax[3]=",0,(char*)NULL);
   G__memvar_setup((void*)(&DetDef::pecalTRmin),102,0,0,-1,G__defined_typename("Float_t"),-1,1,"pecalTRmin[3]=",0,(char*)NULL);
   G__memvar_setup((void*)(&DetDef::pecalTRmax),102,0,0,-1,G__defined_typename("Float_t"),-1,1,"pecalTRmax[3]=",0,(char*)NULL);
   G__memvar_setup((void*)(&DetDef::pecalBLmin),102,0,0,-1,G__defined_typename("Float_t"),-1,1,"pecalBLmin[3]=",0,(char*)NULL);
   G__memvar_setup((void*)(&DetDef::pecalBLmax),102,0,0,-1,G__defined_typename("Float_t"),-1,1,"pecalBLmax[3]=",0,(char*)NULL);
   G__memvar_setup((void*)(&DetDef::pecalBRmin),102,0,0,-1,G__defined_typename("Float_t"),-1,1,"pecalBRmin[3]=",0,(char*)NULL);
   G__memvar_setup((void*)(&DetDef::pecalBRmax),102,0,0,-1,G__defined_typename("Float_t"),-1,1,"pecalBRmax[3]=",0,(char*)NULL);
   G__memvar_setup((void*)(&DetDef::smrd15Lmin),102,0,0,-1,G__defined_typename("Float_t"),-1,1,"smrd15Lmin[3]=",0,(char*)NULL);
   G__memvar_setup((void*)(&DetDef::smrd15Lmax),102,0,0,-1,G__defined_typename("Float_t"),-1,1,"smrd15Lmax[3]=",0,(char*)NULL);
   G__memvar_setup((void*)(&DetDef::smrd6Lmin),102,0,0,-1,G__defined_typename("Float_t"),-1,1,"smrd6Lmin[3]=",0,(char*)NULL);
   G__memvar_setup((void*)(&DetDef::smrd6Lmax),102,0,0,-1,G__defined_typename("Float_t"),-1,1,"smrd6Lmax[3]=",0,(char*)NULL);
   G__memvar_setup((void*)(&DetDef::smrd78Lmin),102,0,0,-1,G__defined_typename("Float_t"),-1,1,"smrd78Lmin[3]=",0,(char*)NULL);
   G__memvar_setup((void*)(&DetDef::smrd78Lmax),102,0,0,-1,G__defined_typename("Float_t"),-1,1,"smrd78Lmax[3]=",0,(char*)NULL);
   G__memvar_setup((void*)(&DetDef::smrd15Rmin),102,0,0,-1,G__defined_typename("Float_t"),-1,1,"smrd15Rmin[3]=",0,(char*)NULL);
   G__memvar_setup((void*)(&DetDef::smrd15Rmax),102,0,0,-1,G__defined_typename("Float_t"),-1,1,"smrd15Rmax[3]=",0,(char*)NULL);
   G__memvar_setup((void*)(&DetDef::smrd6Rmin),102,0,0,-1,G__defined_typename("Float_t"),-1,1,"smrd6Rmin[3]=",0,(char*)NULL);
   G__memvar_setup((void*)(&DetDef::smrd6Rmax),102,0,0,-1,G__defined_typename("Float_t"),-1,1,"smrd6Rmax[3]=",0,(char*)NULL);
   G__memvar_setup((void*)(&DetDef::smrd78Rmin),102,0,0,-1,G__defined_typename("Float_t"),-1,1,"smrd78Rmin[3]=",0,(char*)NULL);
   G__memvar_setup((void*)(&DetDef::smrd78Rmax),102,0,0,-1,G__defined_typename("Float_t"),-1,1,"smrd78Rmax[3]=",0,(char*)NULL);
   G__memvar_setup((void*)(&DetDef::smrdBLmin),102,0,0,-1,G__defined_typename("Float_t"),-1,1,"smrdBLmin[3]=",0,(char*)NULL);
   G__memvar_setup((void*)(&DetDef::smrdBLmax),102,0,0,-1,G__defined_typename("Float_t"),-1,1,"smrdBLmax[3]=",0,(char*)NULL);
   G__memvar_setup((void*)(&DetDef::smrdBRmin),102,0,0,-1,G__defined_typename("Float_t"),-1,1,"smrdBRmin[3]=",0,(char*)NULL);
   G__memvar_setup((void*)(&DetDef::smrdBRmax),102,0,0,-1,G__defined_typename("Float_t"),-1,1,"smrdBRmax[3]=",0,(char*)NULL);
   G__memvar_setup((void*)(&DetDef::smrdTLmin),102,0,0,-1,G__defined_typename("Float_t"),-1,1,"smrdTLmin[3]=",0,(char*)NULL);
   G__memvar_setup((void*)(&DetDef::smrdTLmax),102,0,0,-1,G__defined_typename("Float_t"),-1,1,"smrdTLmax[3]=",0,(char*)NULL);
   G__memvar_setup((void*)(&DetDef::smrdTRmin),102,0,0,-1,G__defined_typename("Float_t"),-1,1,"smrdTRmin[3]=",0,(char*)NULL);
   G__memvar_setup((void*)(&DetDef::smrdTRmax),102,0,0,-1,G__defined_typename("Float_t"),-1,1,"smrdTRmax[3]=",0,(char*)NULL);
   G__memvar_setup((void*)(&DetDef::tpc1min),102,0,0,-1,G__defined_typename("Float_t"),-1,1,"tpc1min[3]=",0,(char*)NULL);
   G__memvar_setup((void*)(&DetDef::tpc1max),102,0,0,-1,G__defined_typename("Float_t"),-1,1,"tpc1max[3]=",0,(char*)NULL);
   G__memvar_setup((void*)(&DetDef::tpc2min),102,0,0,-1,G__defined_typename("Float_t"),-1,1,"tpc2min[3]=",0,(char*)NULL);
   G__memvar_setup((void*)(&DetDef::tpc2max),102,0,0,-1,G__defined_typename("Float_t"),-1,1,"tpc2max[3]=",0,(char*)NULL);
   G__memvar_setup((void*)(&DetDef::tpc3min),102,0,0,-1,G__defined_typename("Float_t"),-1,1,"tpc3min[3]=",0,(char*)NULL);
   G__memvar_setup((void*)(&DetDef::tpc3max),102,0,0,-1,G__defined_typename("Float_t"),-1,1,"tpc3max[3]=",0,(char*)NULL);
   G__memvar_setup((void*)(&DetDef::tpc1Driftmin),102,0,0,-1,G__defined_typename("Float_t"),-1,1,"tpc1Driftmin[3]=",0,(char*)NULL);
   G__memvar_setup((void*)(&DetDef::tpc1Driftmax),102,0,0,-1,G__defined_typename("Float_t"),-1,1,"tpc1Driftmax[3]=",0,(char*)NULL);
   G__memvar_setup((void*)(&DetDef::tpc2Driftmin),102,0,0,-1,G__defined_typename("Float_t"),-1,1,"tpc2Driftmin[3]=",0,(char*)NULL);
   G__memvar_setup((void*)(&DetDef::tpc2Driftmax),102,0,0,-1,G__defined_typename("Float_t"),-1,1,"tpc2Driftmax[3]=",0,(char*)NULL);
   G__memvar_setup((void*)(&DetDef::tpc3Driftmin),102,0,0,-1,G__defined_typename("Float_t"),-1,1,"tpc3Driftmin[3]=",0,(char*)NULL);
   G__memvar_setup((void*)(&DetDef::tpc3Driftmax),102,0,0,-1,G__defined_typename("Float_t"),-1,1,"tpc3Driftmax[3]=",0,(char*)NULL);
   G__memvar_setup((void*)(&DetDef::tpc1DriftLmin),102,0,0,-1,G__defined_typename("Float_t"),-1,1,"tpc1DriftLmin[3]=",0,(char*)NULL);
   G__memvar_setup((void*)(&DetDef::tpc1DriftLmax),102,0,0,-1,G__defined_typename("Float_t"),-1,1,"tpc1DriftLmax[3]=",0,(char*)NULL);
   G__memvar_setup((void*)(&DetDef::tpc2DriftLmin),102,0,0,-1,G__defined_typename("Float_t"),-1,1,"tpc2DriftLmin[3]=",0,(char*)NULL);
   G__memvar_setup((void*)(&DetDef::tpc2DriftLmax),102,0,0,-1,G__defined_typename("Float_t"),-1,1,"tpc2DriftLmax[3]=",0,(char*)NULL);
   G__memvar_setup((void*)(&DetDef::tpc3DriftLmin),102,0,0,-1,G__defined_typename("Float_t"),-1,1,"tpc3DriftLmin[3]=",0,(char*)NULL);
   G__memvar_setup((void*)(&DetDef::tpc3DriftLmax),102,0,0,-1,G__defined_typename("Float_t"),-1,1,"tpc3DriftLmax[3]=",0,(char*)NULL);
   G__memvar_setup((void*)(&DetDef::tpc1DriftRmin),102,0,0,-1,G__defined_typename("Float_t"),-1,1,"tpc1DriftRmin[3]=",0,(char*)NULL);
   G__memvar_setup((void*)(&DetDef::tpc1DriftRmax),102,0,0,-1,G__defined_typename("Float_t"),-1,1,"tpc1DriftRmax[3]=",0,(char*)NULL);
   G__memvar_setup((void*)(&DetDef::tpc2DriftRmin),102,0,0,-1,G__defined_typename("Float_t"),-1,1,"tpc2DriftRmin[3]=",0,(char*)NULL);
   G__memvar_setup((void*)(&DetDef::tpc2DriftRmax),102,0,0,-1,G__defined_typename("Float_t"),-1,1,"tpc2DriftRmax[3]=",0,(char*)NULL);
   G__memvar_setup((void*)(&DetDef::tpc3DriftRmin),102,0,0,-1,G__defined_typename("Float_t"),-1,1,"tpc3DriftRmin[3]=",0,(char*)NULL);
   G__memvar_setup((void*)(&DetDef::tpc3DriftRmax),102,0,0,-1,G__defined_typename("Float_t"),-1,1,"tpc3DriftRmax[3]=",0,(char*)NULL);
   G__memvar_setup((void*)(&DetDef::tpc1Cathodemin),102,0,0,-1,G__defined_typename("Float_t"),-1,1,"tpc1Cathodemin[3]=",0,(char*)NULL);
   G__memvar_setup((void*)(&DetDef::tpc1Cathodemax),102,0,0,-1,G__defined_typename("Float_t"),-1,1,"tpc1Cathodemax[3]=",0,(char*)NULL);
   G__memvar_setup((void*)(&DetDef::tpc2Cathodemin),102,0,0,-1,G__defined_typename("Float_t"),-1,1,"tpc2Cathodemin[3]=",0,(char*)NULL);
   G__memvar_setup((void*)(&DetDef::tpc2Cathodemax),102,0,0,-1,G__defined_typename("Float_t"),-1,1,"tpc2Cathodemax[3]=",0,(char*)NULL);
   G__memvar_setup((void*)(&DetDef::tpc3Cathodemin),102,0,0,-1,G__defined_typename("Float_t"),-1,1,"tpc3Cathodemin[3]=",0,(char*)NULL);
   G__memvar_setup((void*)(&DetDef::tpc3Cathodemax),102,0,0,-1,G__defined_typename("Float_t"),-1,1,"tpc3Cathodemax[3]=",0,(char*)NULL);
   G__memvar_setup((void*)(&DetDef::trackerAllmin),102,0,0,-1,G__defined_typename("Float_t"),-1,1,"trackerAllmin[3]=",0,(char*)NULL);
   G__memvar_setup((void*)(&DetDef::trackerAllmax),102,0,0,-1,G__defined_typename("Float_t"),-1,1,"trackerAllmax[3]=",0,(char*)NULL);
   G__memvar_setup((void*)(&DetDef::fgd2BarCenterMC),102,0,0,-1,G__defined_typename("Float_t"),-1,1,"fgd2BarCenterMC[14]=",0,(char*)NULL);
   G__memvar_setup((void*)(&DetDef::fgd2BarCenterDATA),102,0,0,-1,G__defined_typename("Float_t"),-1,1,"fgd2BarCenterDATA[14]=",0,(char*)NULL);
   G__memvar_setup((void*)(&DetDef::fgd2BarCenter),102,0,0,-1,G__defined_typename("Float_t"),-1,1,"fgd2BarCenter[14]=",0,(char*)NULL);
   G__memvar_setup((void*)(&DetDef::fgd1BarCenter),102,0,0,-1,G__defined_typename("Float_t"),-1,1,"fgd1BarCenter[30]=",0,(char*)NULL);
   G__memvar_setup((void*)(&DetDef::fgd2WaterCenterMC),102,0,0,-1,G__defined_typename("Float_t"),-1,1,"fgd2WaterCenterMC[6]=",0,(char*)NULL);
   G__memvar_setup((void*)(&DetDef::fgd2WaterCenterDATA),102,0,0,-1,G__defined_typename("Float_t"),-1,1,"fgd2WaterCenterDATA[6]=",0,(char*)NULL);
   G__memvar_setup((void*)(&DetDef::fgd2WaterCenter),102,0,0,-1,G__defined_typename("Float_t"),-1,1,"fgd2WaterCenter[6]=",0,(char*)NULL);
   G__memvar_setup((void*)(&DetDef::fgdXYModuleWidth),102,0,0,-1,G__defined_typename("Float_t"),-1,1,"fgdXYModuleWidth=",0,(char*)NULL);
   G__memvar_setup((void*)(&DetDef::fgdXYAirWidth),102,0,0,-1,G__defined_typename("Float_t"),-1,1,"fgdXYAirWidth=",0,(char*)NULL);
   G__memvar_setup((void*)(&DetDef::fgdXYBarWidth),102,0,0,-1,G__defined_typename("Float_t"),-1,1,"fgdXYBarWidth=",0,(char*)NULL);
   G__memvar_setup((void*)(&DetDef::fgdXYMiddleGlueWidth),102,0,0,-1,G__defined_typename("Float_t"),-1,1,"fgdXYMiddleGlueWidth=",0,(char*)NULL);
   G__memvar_setup((void*)(&DetDef::fgdXYGlueWidth),102,0,0,-1,G__defined_typename("Float_t"),-1,1,"fgdXYGlueWidth=",0,(char*)NULL);
   G__memvar_setup((void*)(&DetDef::fgdXYSkinWidth),102,0,0,-1,G__defined_typename("Float_t"),-1,1,"fgdXYSkinWidth=",0,(char*)NULL);
   G__memvar_setup((void*)(&DetDef::fgdWaterModuleWidth),102,0,0,-1,G__defined_typename("Float_t"),-1,1,"fgdWaterModuleWidth=",0,(char*)NULL);
   G__memvar_setup((void*)(&DetDef::fgdWaterAirWidth),102,0,0,-1,G__defined_typename("Float_t"),-1,1,"fgdWaterAirWidth=",0,(char*)NULL);
   G__memvar_setup((void*)(&DetDef::fgdWaterPCWidth),102,0,0,-1,G__defined_typename("Float_t"),-1,1,"fgdWaterPCWidth=",0,(char*)NULL);
   G__memvar_setup((void*)(&DetDef::fgdWaterGlueWidth),102,0,0,-1,G__defined_typename("Float_t"),-1,1,"fgdWaterGlueWidth=",0,(char*)NULL);
   G__memvar_setup((void*)(&DetDef::fgdWaterSkinWidth),102,0,0,-1,G__defined_typename("Float_t"),-1,1,"fgdWaterSkinWidth=",0,(char*)NULL);
   G__memvar_setup((void*)(&DetDef::tecalLmin_p6_data),102,0,0,-1,G__defined_typename("Float_t"),-1,1,"tecalLmin_p6_data[3]=",0,(char*)NULL);
   G__memvar_setup((void*)(&DetDef::tecalLmax_p6_data),102,0,0,-1,G__defined_typename("Float_t"),-1,1,"tecalLmax_p6_data[3]=",0,(char*)NULL);
   G__memvar_setup((void*)(&DetDef::tecalRmin_p6_data),102,0,0,-1,G__defined_typename("Float_t"),-1,1,"tecalRmin_p6_data[3]=",0,(char*)NULL);
   G__memvar_setup((void*)(&DetDef::tecalRmax_p6_data),102,0,0,-1,G__defined_typename("Float_t"),-1,1,"tecalRmax_p6_data[3]=",0,(char*)NULL);
   G__memvar_setup((void*)(&DetDef::tecalTLmin_p6_data),102,0,0,-1,G__defined_typename("Float_t"),-1,1,"tecalTLmin_p6_data[3]=",0,(char*)NULL);
   G__memvar_setup((void*)(&DetDef::tecalTLmax_p6_data),102,0,0,-1,G__defined_typename("Float_t"),-1,1,"tecalTLmax_p6_data[3]=",0,(char*)NULL);
   G__memvar_setup((void*)(&DetDef::tecalTRmin_p6_data),102,0,0,-1,G__defined_typename("Float_t"),-1,1,"tecalTRmin_p6_data[3]=",0,(char*)NULL);
   G__memvar_setup((void*)(&DetDef::tecalTRmax_p6_data),102,0,0,-1,G__defined_typename("Float_t"),-1,1,"tecalTRmax_p6_data[3]=",0,(char*)NULL);
   G__memvar_setup((void*)(&DetDef::tecalBLmin_p6_data),102,0,0,-1,G__defined_typename("Float_t"),-1,1,"tecalBLmin_p6_data[3]=",0,(char*)NULL);
   G__memvar_setup((void*)(&DetDef::tecalBLmax_p6_data),102,0,0,-1,G__defined_typename("Float_t"),-1,1,"tecalBLmax_p6_data[3]=",0,(char*)NULL);
   G__memvar_setup((void*)(&DetDef::tecalBRmin_p6_data),102,0,0,-1,G__defined_typename("Float_t"),-1,1,"tecalBRmin_p6_data[3]=",0,(char*)NULL);
   G__memvar_setup((void*)(&DetDef::tecalBRmax_p6_data),102,0,0,-1,G__defined_typename("Float_t"),-1,1,"tecalBRmax_p6_data[3]=",0,(char*)NULL);
   }
   G__tag_memvar_reset();
}

extern "C" void G__cpp_setup_memvarG_DetectorDefinition() {
}
/***********************************************************
************************************************************
************************************************************
************************************************************
************************************************************
************************************************************
************************************************************
***********************************************************/

/*********************************************************
* Member function information setup for each class
*********************************************************/
static void G__setup_memfuncDetDef(void) {
   /* DetDef */
   G__tag_memfunc_setup(G__get_linked_tagnum(&G__G_DetectorDefinitionLN_DetDef));
   G__memfunc_setup("DumpVolumes",1153,G__G_DetectorDefinition_221_0_1, 121, -1, -1, 0, 0, 1, 1, 0, "", (char*)NULL, (void*) G__func2void( (void (*)())(&DetDef::DumpVolumes) ), 0);
   G__memfunc_setup("DumpFGDInfo",1011,G__G_DetectorDefinition_221_0_2, 121, -1, -1, 0, 0, 1, 1, 0, "", (char*)NULL, (void*) G__func2void( (void (*)())(&DetDef::DumpFGDInfo) ), 0);
   G__tag_memfunc_reset();
}


/*********************************************************
* Member function information setup
*********************************************************/
extern "C" void G__cpp_setup_memfuncG_DetectorDefinition() {
}

/*********************************************************
* Global variable information setup for each class
*********************************************************/
static void G__cpp_setup_global0() {

   /* Setting up global variables */
   G__resetplocal();

}

static void G__cpp_setup_global1() {

   G__resetglobalenv();
}
extern "C" void G__cpp_setup_globalG_DetectorDefinition() {
  G__cpp_setup_global0();
  G__cpp_setup_global1();
}

/*********************************************************
* Global function information setup for each class
*********************************************************/
static void G__cpp_setup_func0() {
   G__lastifuncposition();

}

static void G__cpp_setup_func1() {
}

static void G__cpp_setup_func2() {
}

static void G__cpp_setup_func3() {
}

static void G__cpp_setup_func4() {
}

static void G__cpp_setup_func5() {
}

static void G__cpp_setup_func6() {
}

static void G__cpp_setup_func7() {
}

static void G__cpp_setup_func8() {
}

static void G__cpp_setup_func9() {
}

static void G__cpp_setup_func10() {
}

static void G__cpp_setup_func11() {
}

static void G__cpp_setup_func12() {
}

static void G__cpp_setup_func13() {
}

static void G__cpp_setup_func14() {
}

static void G__cpp_setup_func15() {
}

static void G__cpp_setup_func16() {
}

static void G__cpp_setup_func17() {
}

static void G__cpp_setup_func18() {
}

static void G__cpp_setup_func19() {
}

static void G__cpp_setup_func20() {
}

static void G__cpp_setup_func21() {
}

static void G__cpp_setup_func22() {

   G__resetifuncposition();
}

extern "C" void G__cpp_setup_funcG_DetectorDefinition() {
  G__cpp_setup_func0();
  G__cpp_setup_func1();
  G__cpp_setup_func2();
  G__cpp_setup_func3();
  G__cpp_setup_func4();
  G__cpp_setup_func5();
  G__cpp_setup_func6();
  G__cpp_setup_func7();
  G__cpp_setup_func8();
  G__cpp_setup_func9();
  G__cpp_setup_func10();
  G__cpp_setup_func11();
  G__cpp_setup_func12();
  G__cpp_setup_func13();
  G__cpp_setup_func14();
  G__cpp_setup_func15();
  G__cpp_setup_func16();
  G__cpp_setup_func17();
  G__cpp_setup_func18();
  G__cpp_setup_func19();
  G__cpp_setup_func20();
  G__cpp_setup_func21();
  G__cpp_setup_func22();
}

/*********************************************************
* Class,struct,union,enum tag information setup
*********************************************************/
/* Setup class/struct taginfo */
G__linked_taginfo G__G_DetectorDefinitionLN_vectorlEROOTcLcLTSchemaHelpercOallocatorlEROOTcLcLTSchemaHelpergRsPgR = { "vector<ROOT::TSchemaHelper,allocator<ROOT::TSchemaHelper> >" , 99 , -1 };
G__linked_taginfo G__G_DetectorDefinitionLN_reverse_iteratorlEvectorlEROOTcLcLTSchemaHelpercOallocatorlEROOTcLcLTSchemaHelpergRsPgRcLcLiteratorgR = { "reverse_iterator<vector<ROOT::TSchemaHelper,allocator<ROOT::TSchemaHelper> >::iterator>" , 99 , -1 };
G__linked_taginfo G__G_DetectorDefinitionLN_vectorlETVirtualArraymUcOallocatorlETVirtualArraymUgRsPgR = { "vector<TVirtualArray*,allocator<TVirtualArray*> >" , 99 , -1 };
G__linked_taginfo G__G_DetectorDefinitionLN_reverse_iteratorlEvectorlETVirtualArraymUcOallocatorlETVirtualArraymUgRsPgRcLcLiteratorgR = { "reverse_iterator<vector<TVirtualArray*,allocator<TVirtualArray*> >::iterator>" , 99 , -1 };
G__linked_taginfo G__G_DetectorDefinitionLN_TMatrixTBaselEfloatgR = { "TMatrixTBase<float>" , 99 , -1 };
G__linked_taginfo G__G_DetectorDefinitionLN_TMatrixTBaselEdoublegR = { "TMatrixTBase<double>" , 99 , -1 };
G__linked_taginfo G__G_DetectorDefinitionLN_TVectorTlEfloatgR = { "TVectorT<float>" , 99 , -1 };
G__linked_taginfo G__G_DetectorDefinitionLN_TVectorTlEdoublegR = { "TVectorT<double>" , 99 , -1 };
G__linked_taginfo G__G_DetectorDefinitionLN_TElementActionTlEfloatgR = { "TElementActionT<float>" , 99 , -1 };
G__linked_taginfo G__G_DetectorDefinitionLN_TElementPosActionTlEfloatgR = { "TElementPosActionT<float>" , 99 , -1 };
G__linked_taginfo G__G_DetectorDefinitionLN_TMatrixTlEfloatgR = { "TMatrixT<float>" , 99 , -1 };
G__linked_taginfo G__G_DetectorDefinitionLN_TMatrixTRow_constlEfloatgR = { "TMatrixTRow_const<float>" , 99 , -1 };
G__linked_taginfo G__G_DetectorDefinitionLN_TMatrixTRowlEfloatgR = { "TMatrixTRow<float>" , 99 , -1 };
G__linked_taginfo G__G_DetectorDefinitionLN_TMatrixTDiag_constlEfloatgR = { "TMatrixTDiag_const<float>" , 99 , -1 };
G__linked_taginfo G__G_DetectorDefinitionLN_TMatrixTColumn_constlEfloatgR = { "TMatrixTColumn_const<float>" , 99 , -1 };
G__linked_taginfo G__G_DetectorDefinitionLN_TMatrixTFlat_constlEfloatgR = { "TMatrixTFlat_const<float>" , 99 , -1 };
G__linked_taginfo G__G_DetectorDefinitionLN_TMatrixTSub_constlEfloatgR = { "TMatrixTSub_const<float>" , 99 , -1 };
G__linked_taginfo G__G_DetectorDefinitionLN_TMatrixTSparseRow_constlEfloatgR = { "TMatrixTSparseRow_const<float>" , 99 , -1 };
G__linked_taginfo G__G_DetectorDefinitionLN_TMatrixTSparseDiag_constlEfloatgR = { "TMatrixTSparseDiag_const<float>" , 99 , -1 };
G__linked_taginfo G__G_DetectorDefinitionLN_TMatrixTColumnlEfloatgR = { "TMatrixTColumn<float>" , 99 , -1 };
G__linked_taginfo G__G_DetectorDefinitionLN_TMatrixTDiaglEfloatgR = { "TMatrixTDiag<float>" , 99 , -1 };
G__linked_taginfo G__G_DetectorDefinitionLN_TMatrixTFlatlEfloatgR = { "TMatrixTFlat<float>" , 99 , -1 };
G__linked_taginfo G__G_DetectorDefinitionLN_TMatrixTSublEfloatgR = { "TMatrixTSub<float>" , 99 , -1 };
G__linked_taginfo G__G_DetectorDefinitionLN_TMatrixTSparseRowlEfloatgR = { "TMatrixTSparseRow<float>" , 99 , -1 };
G__linked_taginfo G__G_DetectorDefinitionLN_TMatrixTSparseDiaglEfloatgR = { "TMatrixTSparseDiag<float>" , 99 , -1 };
G__linked_taginfo G__G_DetectorDefinitionLN_DetDef = { "DetDef" , 110 , -1 };

/* Reset class/struct taginfo */
extern "C" void G__cpp_reset_tagtableG_DetectorDefinition() {
  G__G_DetectorDefinitionLN_vectorlEROOTcLcLTSchemaHelpercOallocatorlEROOTcLcLTSchemaHelpergRsPgR.tagnum = -1 ;
  G__G_DetectorDefinitionLN_reverse_iteratorlEvectorlEROOTcLcLTSchemaHelpercOallocatorlEROOTcLcLTSchemaHelpergRsPgRcLcLiteratorgR.tagnum = -1 ;
  G__G_DetectorDefinitionLN_vectorlETVirtualArraymUcOallocatorlETVirtualArraymUgRsPgR.tagnum = -1 ;
  G__G_DetectorDefinitionLN_reverse_iteratorlEvectorlETVirtualArraymUcOallocatorlETVirtualArraymUgRsPgRcLcLiteratorgR.tagnum = -1 ;
  G__G_DetectorDefinitionLN_TMatrixTBaselEfloatgR.tagnum = -1 ;
  G__G_DetectorDefinitionLN_TMatrixTBaselEdoublegR.tagnum = -1 ;
  G__G_DetectorDefinitionLN_TVectorTlEfloatgR.tagnum = -1 ;
  G__G_DetectorDefinitionLN_TVectorTlEdoublegR.tagnum = -1 ;
  G__G_DetectorDefinitionLN_TElementActionTlEfloatgR.tagnum = -1 ;
  G__G_DetectorDefinitionLN_TElementPosActionTlEfloatgR.tagnum = -1 ;
  G__G_DetectorDefinitionLN_TMatrixTlEfloatgR.tagnum = -1 ;
  G__G_DetectorDefinitionLN_TMatrixTRow_constlEfloatgR.tagnum = -1 ;
  G__G_DetectorDefinitionLN_TMatrixTRowlEfloatgR.tagnum = -1 ;
  G__G_DetectorDefinitionLN_TMatrixTDiag_constlEfloatgR.tagnum = -1 ;
  G__G_DetectorDefinitionLN_TMatrixTColumn_constlEfloatgR.tagnum = -1 ;
  G__G_DetectorDefinitionLN_TMatrixTFlat_constlEfloatgR.tagnum = -1 ;
  G__G_DetectorDefinitionLN_TMatrixTSub_constlEfloatgR.tagnum = -1 ;
  G__G_DetectorDefinitionLN_TMatrixTSparseRow_constlEfloatgR.tagnum = -1 ;
  G__G_DetectorDefinitionLN_TMatrixTSparseDiag_constlEfloatgR.tagnum = -1 ;
  G__G_DetectorDefinitionLN_TMatrixTColumnlEfloatgR.tagnum = -1 ;
  G__G_DetectorDefinitionLN_TMatrixTDiaglEfloatgR.tagnum = -1 ;
  G__G_DetectorDefinitionLN_TMatrixTFlatlEfloatgR.tagnum = -1 ;
  G__G_DetectorDefinitionLN_TMatrixTSublEfloatgR.tagnum = -1 ;
  G__G_DetectorDefinitionLN_TMatrixTSparseRowlEfloatgR.tagnum = -1 ;
  G__G_DetectorDefinitionLN_TMatrixTSparseDiaglEfloatgR.tagnum = -1 ;
  G__G_DetectorDefinitionLN_DetDef.tagnum = -1 ;
}


extern "C" void G__cpp_setup_tagtableG_DetectorDefinition() {

   /* Setting up class,struct,union tag entry */
   G__get_linked_tagnum_fwd(&G__G_DetectorDefinitionLN_vectorlEROOTcLcLTSchemaHelpercOallocatorlEROOTcLcLTSchemaHelpergRsPgR);
   G__get_linked_tagnum_fwd(&G__G_DetectorDefinitionLN_reverse_iteratorlEvectorlEROOTcLcLTSchemaHelpercOallocatorlEROOTcLcLTSchemaHelpergRsPgRcLcLiteratorgR);
   G__get_linked_tagnum_fwd(&G__G_DetectorDefinitionLN_vectorlETVirtualArraymUcOallocatorlETVirtualArraymUgRsPgR);
   G__get_linked_tagnum_fwd(&G__G_DetectorDefinitionLN_reverse_iteratorlEvectorlETVirtualArraymUcOallocatorlETVirtualArraymUgRsPgRcLcLiteratorgR);
   G__get_linked_tagnum_fwd(&G__G_DetectorDefinitionLN_TMatrixTBaselEfloatgR);
   G__get_linked_tagnum_fwd(&G__G_DetectorDefinitionLN_TMatrixTBaselEdoublegR);
   G__get_linked_tagnum_fwd(&G__G_DetectorDefinitionLN_TVectorTlEfloatgR);
   G__get_linked_tagnum_fwd(&G__G_DetectorDefinitionLN_TVectorTlEdoublegR);
   G__get_linked_tagnum_fwd(&G__G_DetectorDefinitionLN_TElementActionTlEfloatgR);
   G__get_linked_tagnum_fwd(&G__G_DetectorDefinitionLN_TElementPosActionTlEfloatgR);
   G__get_linked_tagnum_fwd(&G__G_DetectorDefinitionLN_TMatrixTlEfloatgR);
   G__get_linked_tagnum_fwd(&G__G_DetectorDefinitionLN_TMatrixTRow_constlEfloatgR);
   G__get_linked_tagnum_fwd(&G__G_DetectorDefinitionLN_TMatrixTRowlEfloatgR);
   G__get_linked_tagnum_fwd(&G__G_DetectorDefinitionLN_TMatrixTDiag_constlEfloatgR);
   G__get_linked_tagnum_fwd(&G__G_DetectorDefinitionLN_TMatrixTColumn_constlEfloatgR);
   G__get_linked_tagnum_fwd(&G__G_DetectorDefinitionLN_TMatrixTFlat_constlEfloatgR);
   G__get_linked_tagnum_fwd(&G__G_DetectorDefinitionLN_TMatrixTSub_constlEfloatgR);
   G__get_linked_tagnum_fwd(&G__G_DetectorDefinitionLN_TMatrixTSparseRow_constlEfloatgR);
   G__get_linked_tagnum_fwd(&G__G_DetectorDefinitionLN_TMatrixTSparseDiag_constlEfloatgR);
   G__get_linked_tagnum_fwd(&G__G_DetectorDefinitionLN_TMatrixTColumnlEfloatgR);
   G__get_linked_tagnum_fwd(&G__G_DetectorDefinitionLN_TMatrixTDiaglEfloatgR);
   G__get_linked_tagnum_fwd(&G__G_DetectorDefinitionLN_TMatrixTFlatlEfloatgR);
   G__get_linked_tagnum_fwd(&G__G_DetectorDefinitionLN_TMatrixTSublEfloatgR);
   G__get_linked_tagnum_fwd(&G__G_DetectorDefinitionLN_TMatrixTSparseRowlEfloatgR);
   G__get_linked_tagnum_fwd(&G__G_DetectorDefinitionLN_TMatrixTSparseDiaglEfloatgR);
   G__tagtable_setup(G__get_linked_tagnum_fwd(&G__G_DetectorDefinitionLN_DetDef),0,-1,0,(char*)NULL,G__setup_memvarDetDef,G__setup_memfuncDetDef);
}
extern "C" void G__cpp_setupG_DetectorDefinition(void) {
  G__check_setup_version(30051515,"G__cpp_setupG_DetectorDefinition()");
  G__set_cpp_environmentG_DetectorDefinition();
  G__cpp_setup_tagtableG_DetectorDefinition();

  G__cpp_setup_inheritanceG_DetectorDefinition();

  G__cpp_setup_typetableG_DetectorDefinition();

  G__cpp_setup_memvarG_DetectorDefinition();

  G__cpp_setup_memfuncG_DetectorDefinition();
  G__cpp_setup_globalG_DetectorDefinition();
  G__cpp_setup_funcG_DetectorDefinition();

   if(0==G__getsizep2memfunc()) G__get_sizep2memfuncG_DetectorDefinition();
  return;
}
class G__cpp_setup_initG_DetectorDefinition {
  public:
    G__cpp_setup_initG_DetectorDefinition() { G__add_setup_func("G_DetectorDefinition",(G__incsetup)(&G__cpp_setupG_DetectorDefinition)); G__call_setup_funcs(); }
   ~G__cpp_setup_initG_DetectorDefinition() { G__remove_setup_func("G_DetectorDefinition"); }
};
G__cpp_setup_initG_DetectorDefinition G__cpp_setup_initializerG_DetectorDefinition;
