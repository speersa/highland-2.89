//
// File generated by /t2k/Software/v12r25/ROOT/v5r34p34n00/Linux-x86_64//bin/rootcint at Thu Apr 20 02:09:33 2023

// Do NOT change. Changes will be lost next time file is generated
//

#define R__DICTIONARY_FILENAME dIhomedIt2kdIaspeersdIHighland_InstallsdIHighLAND_2dO89dIpsycheND280Utils_3dO73dILinuxmICentOS_7mIgcc_4dO8mIx86_64dIdictdIG_FiducialVolumeDefinition
#include "RConfig.h" //rootcint 4834
#if !defined(R__ACCESS_IN_SYMBOL)
//Break the privacy of classes -- Disabled for the moment
#define private public
#define protected public
#endif

// Since CINT ignores the std namespace, we need to do so in this file.
namespace std {} using namespace std;
#include "G_FiducialVolumeDefinition.h"

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

namespace FVDef {
   namespace ROOTDict {
      inline ::ROOT::TGenericClassInfo *GenerateInitInstance();
      static void FVDef_Dictionary();

      // Function generating the singleton type initializer
      inline ::ROOT::TGenericClassInfo *GenerateInitInstance()
      {
         static ::ROOT::TGenericClassInfo 
            instance("FVDef", 0 /*version*/, "/home/t2k/aspeers/Highland_Installs/HighLAND_2.89/psycheND280Utils_3.73/inc/FiducialVolumeDefinition.hxx", 10,
                     ::ROOT::DefineBehavior((void*)0,(void*)0),
                     &FVDef_Dictionary, 0);
         return &instance;
      }
      // Insure that the inline function is _not_ optimized away by the compiler
      ::ROOT::TGenericClassInfo *(*_R__UNIQUE_(InitFunctionKeeper))() = &GenerateInitInstance;  
      // Static variable to force the class initialization
      static ::ROOT::TGenericClassInfo *_R__UNIQUE_(Init) = GenerateInitInstance(); R__UseDummy(_R__UNIQUE_(Init));

      // Dictionary for non-ClassDef classes
      static void FVDef_Dictionary() {
         GenerateInitInstance()->GetClass();
      }

   }
}

/********************************************************
* /home/t2k/aspeers/Highland_Installs/HighLAND_2.89/psycheND280Utils_3.73/Linux-CentOS_7-gcc_4.8-x86_64/dict/G_FiducialVolumeDefinition.cxx
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

extern "C" void G__cpp_reset_tagtableG_FiducialVolumeDefinition();

extern "C" void G__set_cpp_environmentG_FiducialVolumeDefinition() {
  G__cpp_reset_tagtableG_FiducialVolumeDefinition();
}
#include <new>
extern "C" int G__cpp_dllrevG_FiducialVolumeDefinition() { return(30051515); }

/*********************************************************
* Member function Interface Method
*********************************************************/

/* FVDef */
static int G__G_FiducialVolumeDefinition_221_0_1(G__value* result7, G__CONST char* funcname, struct G__param* libp, int hash)
{
      FVDef::SetFVs();
      G__setnull(result7);
   return(1 || funcname || hash || result7 || libp) ;
}

static int G__G_FiducialVolumeDefinition_221_0_2(G__value* result7, G__CONST char* funcname, struct G__param* libp, int hash)
{
      FVDef::DumpFV();
      G__setnull(result7);
   return(1 || funcname || hash || result7 || libp) ;
}


/* Setting up global function */

/*********************************************************
* Member function Stub
*********************************************************/

/* FVDef */

/*********************************************************
* Global function Stub
*********************************************************/

/*********************************************************
* Get size of pointer to member function
*********************************************************/
class G__Sizep2memfuncG_FiducialVolumeDefinition {
 public:
  G__Sizep2memfuncG_FiducialVolumeDefinition(): p(&G__Sizep2memfuncG_FiducialVolumeDefinition::sizep2memfunc) {}
    size_t sizep2memfunc() { return(sizeof(p)); }
  private:
    size_t (G__Sizep2memfuncG_FiducialVolumeDefinition::*p)();
};

size_t G__get_sizep2memfuncG_FiducialVolumeDefinition()
{
  G__Sizep2memfuncG_FiducialVolumeDefinition a;
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
extern "C" void G__cpp_setup_inheritanceG_FiducialVolumeDefinition() {

   /* Setting up class inheritance */
}

/*********************************************************
* typedef information setup/
*********************************************************/
extern "C" void G__cpp_setup_typetableG_FiducialVolumeDefinition() {

   /* Setting up typedef entry */
   G__search_typename2("vector<ROOT::TSchemaHelper>",117,G__get_linked_tagnum(&G__G_FiducialVolumeDefinitionLN_vectorlEROOTcLcLTSchemaHelpercOallocatorlEROOTcLcLTSchemaHelpergRsPgR),0,-1);
   G__setnewtype(-1,NULL,0);
   G__search_typename2("reverse_iterator<const_iterator>",117,G__get_linked_tagnum(&G__G_FiducialVolumeDefinitionLN_reverse_iteratorlEvectorlEROOTcLcLTSchemaHelpercOallocatorlEROOTcLcLTSchemaHelpergRsPgRcLcLiteratorgR),0,G__get_linked_tagnum(&G__G_FiducialVolumeDefinitionLN_vectorlEROOTcLcLTSchemaHelpercOallocatorlEROOTcLcLTSchemaHelpergRsPgR));
   G__setnewtype(-1,NULL,0);
   G__search_typename2("reverse_iterator<iterator>",117,G__get_linked_tagnum(&G__G_FiducialVolumeDefinitionLN_reverse_iteratorlEvectorlEROOTcLcLTSchemaHelpercOallocatorlEROOTcLcLTSchemaHelpergRsPgRcLcLiteratorgR),0,G__get_linked_tagnum(&G__G_FiducialVolumeDefinitionLN_vectorlEROOTcLcLTSchemaHelpercOallocatorlEROOTcLcLTSchemaHelpergRsPgR));
   G__setnewtype(-1,NULL,0);
   G__search_typename2("vector<TVirtualArray*>",117,G__get_linked_tagnum(&G__G_FiducialVolumeDefinitionLN_vectorlETVirtualArraymUcOallocatorlETVirtualArraymUgRsPgR),0,-1);
   G__setnewtype(-1,NULL,0);
   G__search_typename2("reverse_iterator<const_iterator>",117,G__get_linked_tagnum(&G__G_FiducialVolumeDefinitionLN_reverse_iteratorlEvectorlETVirtualArraymUcOallocatorlETVirtualArraymUgRsPgRcLcLiteratorgR),0,G__get_linked_tagnum(&G__G_FiducialVolumeDefinitionLN_vectorlETVirtualArraymUcOallocatorlETVirtualArraymUgRsPgR));
   G__setnewtype(-1,NULL,0);
   G__search_typename2("reverse_iterator<iterator>",117,G__get_linked_tagnum(&G__G_FiducialVolumeDefinitionLN_reverse_iteratorlEvectorlETVirtualArraymUcOallocatorlETVirtualArraymUgRsPgRcLcLiteratorgR),0,G__get_linked_tagnum(&G__G_FiducialVolumeDefinitionLN_vectorlETVirtualArraymUcOallocatorlETVirtualArraymUgRsPgR));
   G__setnewtype(-1,NULL,0);
   G__search_typename2("TMatrixTBase<Float_t>",117,G__get_linked_tagnum(&G__G_FiducialVolumeDefinitionLN_TMatrixTBaselEfloatgR),0,-1);
   G__setnewtype(-1,NULL,0);
   G__search_typename2("TMatrixTBase<Double_t>",117,G__get_linked_tagnum(&G__G_FiducialVolumeDefinitionLN_TMatrixTBaselEdoublegR),0,-1);
   G__setnewtype(-1,NULL,0);
   G__search_typename2("TVectorT<Float_t>",117,G__get_linked_tagnum(&G__G_FiducialVolumeDefinitionLN_TVectorTlEfloatgR),0,-1);
   G__setnewtype(-1,NULL,0);
   G__search_typename2("TVectorT<Double_t>",117,G__get_linked_tagnum(&G__G_FiducialVolumeDefinitionLN_TVectorTlEdoublegR),0,-1);
   G__setnewtype(-1,NULL,0);
   G__search_typename2("TMatrixT<Float_t>",117,G__get_linked_tagnum(&G__G_FiducialVolumeDefinitionLN_TMatrixTlEfloatgR),0,-1);
   G__setnewtype(-1,NULL,0);
   G__search_typename2("TMatrixTRow_const<Float_t>",117,G__get_linked_tagnum(&G__G_FiducialVolumeDefinitionLN_TMatrixTRow_constlEfloatgR),0,-1);
   G__setnewtype(-1,NULL,0);
   G__search_typename2("TMatrixTColumn_const<Float_t>",117,G__get_linked_tagnum(&G__G_FiducialVolumeDefinitionLN_TMatrixTColumn_constlEfloatgR),0,-1);
   G__setnewtype(-1,NULL,0);
   G__search_typename2("TMatrixTDiag_const<Float_t>",117,G__get_linked_tagnum(&G__G_FiducialVolumeDefinitionLN_TMatrixTDiag_constlEfloatgR),0,-1);
   G__setnewtype(-1,NULL,0);
   G__search_typename2("TMatrixTFlat_const<Float_t>",117,G__get_linked_tagnum(&G__G_FiducialVolumeDefinitionLN_TMatrixTFlat_constlEfloatgR),0,-1);
   G__setnewtype(-1,NULL,0);
   G__search_typename2("TMatrixTSub_const<Float_t>",117,G__get_linked_tagnum(&G__G_FiducialVolumeDefinitionLN_TMatrixTSub_constlEfloatgR),0,-1);
   G__setnewtype(-1,NULL,0);
   G__search_typename2("TMatrixTSparseRow_const<Float_t>",117,G__get_linked_tagnum(&G__G_FiducialVolumeDefinitionLN_TMatrixTSparseRow_constlEfloatgR),0,-1);
   G__setnewtype(-1,NULL,0);
   G__search_typename2("TMatrixTSparseDiag_const<Float_t>",117,G__get_linked_tagnum(&G__G_FiducialVolumeDefinitionLN_TMatrixTSparseDiag_constlEfloatgR),0,-1);
   G__setnewtype(-1,NULL,0);
   G__search_typename2("TMatrixTRow<Float_t>",117,G__get_linked_tagnum(&G__G_FiducialVolumeDefinitionLN_TMatrixTRowlEfloatgR),0,-1);
   G__setnewtype(-1,NULL,0);
   G__search_typename2("TMatrixTColumn<Float_t>",117,G__get_linked_tagnum(&G__G_FiducialVolumeDefinitionLN_TMatrixTColumnlEfloatgR),0,-1);
   G__setnewtype(-1,NULL,0);
   G__search_typename2("TMatrixTDiag<Float_t>",117,G__get_linked_tagnum(&G__G_FiducialVolumeDefinitionLN_TMatrixTDiaglEfloatgR),0,-1);
   G__setnewtype(-1,NULL,0);
   G__search_typename2("TMatrixTFlat<Float_t>",117,G__get_linked_tagnum(&G__G_FiducialVolumeDefinitionLN_TMatrixTFlatlEfloatgR),0,-1);
   G__setnewtype(-1,NULL,0);
   G__search_typename2("TMatrixTSub<Float_t>",117,G__get_linked_tagnum(&G__G_FiducialVolumeDefinitionLN_TMatrixTSublEfloatgR),0,-1);
   G__setnewtype(-1,NULL,0);
   G__search_typename2("TMatrixTSparseRow<Float_t>",117,G__get_linked_tagnum(&G__G_FiducialVolumeDefinitionLN_TMatrixTSparseRowlEfloatgR),0,-1);
   G__setnewtype(-1,NULL,0);
   G__search_typename2("TMatrixTSparseDiag<Float_t>",117,G__get_linked_tagnum(&G__G_FiducialVolumeDefinitionLN_TMatrixTSparseDiaglEfloatgR),0,-1);
   G__setnewtype(-1,NULL,0);
   G__search_typename2("TElementActionT<Float_t>",117,G__get_linked_tagnum(&G__G_FiducialVolumeDefinitionLN_TElementActionTlEfloatgR),0,-1);
   G__setnewtype(-1,NULL,0);
   G__search_typename2("TElementPosActionT<Float_t>",117,G__get_linked_tagnum(&G__G_FiducialVolumeDefinitionLN_TElementPosActionTlEfloatgR),0,-1);
   G__setnewtype(-1,NULL,0);
}

/*********************************************************
* Data Member information setup/
*********************************************************/

   /* Setting up class,struct,union tag member variable */

   /* FVDef */
static void G__setup_memvarFVDef(void) {
   G__tag_memvar_setup(G__get_linked_tagnum(&G__G_FiducialVolumeDefinitionLN_FVDef));
   {
   G__memvar_setup((void*)(&FVDef::FVdefminFGD1),102,0,0,-1,G__defined_typename("Float_t"),-1,1,"FVdefminFGD1[3]=",0,(char*)NULL);
   G__memvar_setup((void*)(&FVDef::FVdefmaxFGD1),102,0,0,-1,G__defined_typename("Float_t"),-1,1,"FVdefmaxFGD1[3]=",0,(char*)NULL);
   G__memvar_setup((void*)(&FVDef::FVdefminFGD2),102,0,0,-1,G__defined_typename("Float_t"),-1,1,"FVdefminFGD2[3]=",0,(char*)NULL);
   G__memvar_setup((void*)(&FVDef::FVdefmaxFGD2),102,0,0,-1,G__defined_typename("Float_t"),-1,1,"FVdefmaxFGD2[3]=",0,(char*)NULL);
   G__memvar_setup((void*)(&FVDef::FVdefminP0D),102,0,0,-1,G__defined_typename("Float_t"),-1,1,"FVdefminP0D[3]=",0,(char*)NULL);
   G__memvar_setup((void*)(&FVDef::FVdefmaxP0D),102,0,0,-1,G__defined_typename("Float_t"),-1,1,"FVdefmaxP0D[3]=",0,(char*)NULL);
   G__memvar_setup((void*)(&FVDef::FVdefminTECALLeft),102,0,0,-1,G__defined_typename("Float_t"),-1,1,"FVdefminTECALLeft[3]=",0,(char*)NULL);
   G__memvar_setup((void*)(&FVDef::FVdefmaxTECALLeft),102,0,0,-1,G__defined_typename("Float_t"),-1,1,"FVdefmaxTECALLeft[3]=",0,(char*)NULL);
   G__memvar_setup((void*)(&FVDef::FVdefminTECALRight),102,0,0,-1,G__defined_typename("Float_t"),-1,1,"FVdefminTECALRight[3]=",0,(char*)NULL);
   G__memvar_setup((void*)(&FVDef::FVdefmaxTECALRight),102,0,0,-1,G__defined_typename("Float_t"),-1,1,"FVdefmaxTECALRight[3]=",0,(char*)NULL);
   G__memvar_setup((void*)(&FVDef::FVdefminTECALTop),102,0,0,-1,G__defined_typename("Float_t"),-1,1,"FVdefminTECALTop[3]=",0,(char*)NULL);
   G__memvar_setup((void*)(&FVDef::FVdefmaxTECALTop),102,0,0,-1,G__defined_typename("Float_t"),-1,1,"FVdefmaxTECALTop[3]=",0,(char*)NULL);
   G__memvar_setup((void*)(&FVDef::FVdefminTECALBottom),102,0,0,-1,G__defined_typename("Float_t"),-1,1,"FVdefminTECALBottom[3]=",0,(char*)NULL);
   G__memvar_setup((void*)(&FVDef::FVdefmaxTECALBottom),102,0,0,-1,G__defined_typename("Float_t"),-1,1,"FVdefmaxTECALBottom[3]=",0,(char*)NULL);
   G__memvar_setup((void*)(&FVDef::FVdefminSMRDLeft),102,0,0,-1,G__defined_typename("Float_t"),-1,1,"FVdefminSMRDLeft[3]=",0,(char*)NULL);
   G__memvar_setup((void*)(&FVDef::FVdefmaxSMRDLeft),102,0,0,-1,G__defined_typename("Float_t"),-1,1,"FVdefmaxSMRDLeft[3]=",0,(char*)NULL);
   G__memvar_setup((void*)(&FVDef::FVdefminSMRDRight),102,0,0,-1,G__defined_typename("Float_t"),-1,1,"FVdefminSMRDRight[3]=",0,(char*)NULL);
   G__memvar_setup((void*)(&FVDef::FVdefmaxSMRDRight),102,0,0,-1,G__defined_typename("Float_t"),-1,1,"FVdefmaxSMRDRight[3]=",0,(char*)NULL);
   G__memvar_setup((void*)(&FVDef::FVdefminSMRDTop),102,0,0,-1,G__defined_typename("Float_t"),-1,1,"FVdefminSMRDTop[3]=",0,(char*)NULL);
   G__memvar_setup((void*)(&FVDef::FVdefmaxSMRDTop),102,0,0,-1,G__defined_typename("Float_t"),-1,1,"FVdefmaxSMRDTop[3]=",0,(char*)NULL);
   G__memvar_setup((void*)(&FVDef::FVdefminSMRDBottom),102,0,0,-1,G__defined_typename("Float_t"),-1,1,"FVdefminSMRDBottom[3]=",0,(char*)NULL);
   G__memvar_setup((void*)(&FVDef::FVdefmaxSMRDBottom),102,0,0,-1,G__defined_typename("Float_t"),-1,1,"FVdefmaxSMRDBottom[3]=",0,(char*)NULL);
   G__memvar_setup((void*)(&FVDef::hlFVdefminFGD1),102,0,0,-1,G__defined_typename("Float_t"),-1,1,"hlFVdefminFGD1[3]=",0,(char*)NULL);
   G__memvar_setup((void*)(&FVDef::hlFVdefmaxFGD1),102,0,0,-1,G__defined_typename("Float_t"),-1,1,"hlFVdefmaxFGD1[3]=",0,(char*)NULL);
   G__memvar_setup((void*)(&FVDef::hlFVdefminFGD2),102,0,0,-1,G__defined_typename("Float_t"),-1,1,"hlFVdefminFGD2[3]=",0,(char*)NULL);
   G__memvar_setup((void*)(&FVDef::hlFVdefmaxFGD2),102,0,0,-1,G__defined_typename("Float_t"),-1,1,"hlFVdefmaxFGD2[3]=",0,(char*)NULL);
   G__memvar_setup((void*)(&FVDef::hlFVdefminP0D),102,0,0,-1,G__defined_typename("Float_t"),-1,1,"hlFVdefminP0D[3]=",0,(char*)NULL);
   G__memvar_setup((void*)(&FVDef::hlFVdefmaxP0D),102,0,0,-1,G__defined_typename("Float_t"),-1,1,"hlFVdefmaxP0D[3]=",0,(char*)NULL);
   }
   G__tag_memvar_reset();
}

extern "C" void G__cpp_setup_memvarG_FiducialVolumeDefinition() {
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
static void G__setup_memfuncFVDef(void) {
   /* FVDef */
   G__tag_memfunc_setup(G__get_linked_tagnum(&G__G_FiducialVolumeDefinitionLN_FVDef));
   G__memfunc_setup("SetFVs",571,G__G_FiducialVolumeDefinition_221_0_1, 121, -1, -1, 0, 0, 1, 1, 0, "", (char*)NULL, (void*) G__func2void( (void (*)())(&FVDef::SetFVs) ), 0);
   G__memfunc_setup("DumpFV",562,G__G_FiducialVolumeDefinition_221_0_2, 121, -1, -1, 0, 0, 1, 1, 0, "", (char*)NULL, (void*) G__func2void( (void (*)())(&FVDef::DumpFV) ), 0);
   G__tag_memfunc_reset();
}


/*********************************************************
* Member function information setup
*********************************************************/
extern "C" void G__cpp_setup_memfuncG_FiducialVolumeDefinition() {
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
extern "C" void G__cpp_setup_globalG_FiducialVolumeDefinition() {
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

extern "C" void G__cpp_setup_funcG_FiducialVolumeDefinition() {
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
G__linked_taginfo G__G_FiducialVolumeDefinitionLN_vectorlEROOTcLcLTSchemaHelpercOallocatorlEROOTcLcLTSchemaHelpergRsPgR = { "vector<ROOT::TSchemaHelper,allocator<ROOT::TSchemaHelper> >" , 99 , -1 };
G__linked_taginfo G__G_FiducialVolumeDefinitionLN_reverse_iteratorlEvectorlEROOTcLcLTSchemaHelpercOallocatorlEROOTcLcLTSchemaHelpergRsPgRcLcLiteratorgR = { "reverse_iterator<vector<ROOT::TSchemaHelper,allocator<ROOT::TSchemaHelper> >::iterator>" , 99 , -1 };
G__linked_taginfo G__G_FiducialVolumeDefinitionLN_vectorlETVirtualArraymUcOallocatorlETVirtualArraymUgRsPgR = { "vector<TVirtualArray*,allocator<TVirtualArray*> >" , 99 , -1 };
G__linked_taginfo G__G_FiducialVolumeDefinitionLN_reverse_iteratorlEvectorlETVirtualArraymUcOallocatorlETVirtualArraymUgRsPgRcLcLiteratorgR = { "reverse_iterator<vector<TVirtualArray*,allocator<TVirtualArray*> >::iterator>" , 99 , -1 };
G__linked_taginfo G__G_FiducialVolumeDefinitionLN_TMatrixTBaselEfloatgR = { "TMatrixTBase<float>" , 99 , -1 };
G__linked_taginfo G__G_FiducialVolumeDefinitionLN_TMatrixTBaselEdoublegR = { "TMatrixTBase<double>" , 99 , -1 };
G__linked_taginfo G__G_FiducialVolumeDefinitionLN_TVectorTlEfloatgR = { "TVectorT<float>" , 99 , -1 };
G__linked_taginfo G__G_FiducialVolumeDefinitionLN_TVectorTlEdoublegR = { "TVectorT<double>" , 99 , -1 };
G__linked_taginfo G__G_FiducialVolumeDefinitionLN_TElementActionTlEfloatgR = { "TElementActionT<float>" , 99 , -1 };
G__linked_taginfo G__G_FiducialVolumeDefinitionLN_TElementPosActionTlEfloatgR = { "TElementPosActionT<float>" , 99 , -1 };
G__linked_taginfo G__G_FiducialVolumeDefinitionLN_TMatrixTlEfloatgR = { "TMatrixT<float>" , 99 , -1 };
G__linked_taginfo G__G_FiducialVolumeDefinitionLN_TMatrixTRow_constlEfloatgR = { "TMatrixTRow_const<float>" , 99 , -1 };
G__linked_taginfo G__G_FiducialVolumeDefinitionLN_TMatrixTRowlEfloatgR = { "TMatrixTRow<float>" , 99 , -1 };
G__linked_taginfo G__G_FiducialVolumeDefinitionLN_TMatrixTDiag_constlEfloatgR = { "TMatrixTDiag_const<float>" , 99 , -1 };
G__linked_taginfo G__G_FiducialVolumeDefinitionLN_TMatrixTColumn_constlEfloatgR = { "TMatrixTColumn_const<float>" , 99 , -1 };
G__linked_taginfo G__G_FiducialVolumeDefinitionLN_TMatrixTFlat_constlEfloatgR = { "TMatrixTFlat_const<float>" , 99 , -1 };
G__linked_taginfo G__G_FiducialVolumeDefinitionLN_TMatrixTSub_constlEfloatgR = { "TMatrixTSub_const<float>" , 99 , -1 };
G__linked_taginfo G__G_FiducialVolumeDefinitionLN_TMatrixTSparseRow_constlEfloatgR = { "TMatrixTSparseRow_const<float>" , 99 , -1 };
G__linked_taginfo G__G_FiducialVolumeDefinitionLN_TMatrixTSparseDiag_constlEfloatgR = { "TMatrixTSparseDiag_const<float>" , 99 , -1 };
G__linked_taginfo G__G_FiducialVolumeDefinitionLN_TMatrixTColumnlEfloatgR = { "TMatrixTColumn<float>" , 99 , -1 };
G__linked_taginfo G__G_FiducialVolumeDefinitionLN_TMatrixTDiaglEfloatgR = { "TMatrixTDiag<float>" , 99 , -1 };
G__linked_taginfo G__G_FiducialVolumeDefinitionLN_TMatrixTFlatlEfloatgR = { "TMatrixTFlat<float>" , 99 , -1 };
G__linked_taginfo G__G_FiducialVolumeDefinitionLN_TMatrixTSublEfloatgR = { "TMatrixTSub<float>" , 99 , -1 };
G__linked_taginfo G__G_FiducialVolumeDefinitionLN_TMatrixTSparseRowlEfloatgR = { "TMatrixTSparseRow<float>" , 99 , -1 };
G__linked_taginfo G__G_FiducialVolumeDefinitionLN_TMatrixTSparseDiaglEfloatgR = { "TMatrixTSparseDiag<float>" , 99 , -1 };
G__linked_taginfo G__G_FiducialVolumeDefinitionLN_FVDef = { "FVDef" , 110 , -1 };

/* Reset class/struct taginfo */
extern "C" void G__cpp_reset_tagtableG_FiducialVolumeDefinition() {
  G__G_FiducialVolumeDefinitionLN_vectorlEROOTcLcLTSchemaHelpercOallocatorlEROOTcLcLTSchemaHelpergRsPgR.tagnum = -1 ;
  G__G_FiducialVolumeDefinitionLN_reverse_iteratorlEvectorlEROOTcLcLTSchemaHelpercOallocatorlEROOTcLcLTSchemaHelpergRsPgRcLcLiteratorgR.tagnum = -1 ;
  G__G_FiducialVolumeDefinitionLN_vectorlETVirtualArraymUcOallocatorlETVirtualArraymUgRsPgR.tagnum = -1 ;
  G__G_FiducialVolumeDefinitionLN_reverse_iteratorlEvectorlETVirtualArraymUcOallocatorlETVirtualArraymUgRsPgRcLcLiteratorgR.tagnum = -1 ;
  G__G_FiducialVolumeDefinitionLN_TMatrixTBaselEfloatgR.tagnum = -1 ;
  G__G_FiducialVolumeDefinitionLN_TMatrixTBaselEdoublegR.tagnum = -1 ;
  G__G_FiducialVolumeDefinitionLN_TVectorTlEfloatgR.tagnum = -1 ;
  G__G_FiducialVolumeDefinitionLN_TVectorTlEdoublegR.tagnum = -1 ;
  G__G_FiducialVolumeDefinitionLN_TElementActionTlEfloatgR.tagnum = -1 ;
  G__G_FiducialVolumeDefinitionLN_TElementPosActionTlEfloatgR.tagnum = -1 ;
  G__G_FiducialVolumeDefinitionLN_TMatrixTlEfloatgR.tagnum = -1 ;
  G__G_FiducialVolumeDefinitionLN_TMatrixTRow_constlEfloatgR.tagnum = -1 ;
  G__G_FiducialVolumeDefinitionLN_TMatrixTRowlEfloatgR.tagnum = -1 ;
  G__G_FiducialVolumeDefinitionLN_TMatrixTDiag_constlEfloatgR.tagnum = -1 ;
  G__G_FiducialVolumeDefinitionLN_TMatrixTColumn_constlEfloatgR.tagnum = -1 ;
  G__G_FiducialVolumeDefinitionLN_TMatrixTFlat_constlEfloatgR.tagnum = -1 ;
  G__G_FiducialVolumeDefinitionLN_TMatrixTSub_constlEfloatgR.tagnum = -1 ;
  G__G_FiducialVolumeDefinitionLN_TMatrixTSparseRow_constlEfloatgR.tagnum = -1 ;
  G__G_FiducialVolumeDefinitionLN_TMatrixTSparseDiag_constlEfloatgR.tagnum = -1 ;
  G__G_FiducialVolumeDefinitionLN_TMatrixTColumnlEfloatgR.tagnum = -1 ;
  G__G_FiducialVolumeDefinitionLN_TMatrixTDiaglEfloatgR.tagnum = -1 ;
  G__G_FiducialVolumeDefinitionLN_TMatrixTFlatlEfloatgR.tagnum = -1 ;
  G__G_FiducialVolumeDefinitionLN_TMatrixTSublEfloatgR.tagnum = -1 ;
  G__G_FiducialVolumeDefinitionLN_TMatrixTSparseRowlEfloatgR.tagnum = -1 ;
  G__G_FiducialVolumeDefinitionLN_TMatrixTSparseDiaglEfloatgR.tagnum = -1 ;
  G__G_FiducialVolumeDefinitionLN_FVDef.tagnum = -1 ;
}


extern "C" void G__cpp_setup_tagtableG_FiducialVolumeDefinition() {

   /* Setting up class,struct,union tag entry */
   G__get_linked_tagnum_fwd(&G__G_FiducialVolumeDefinitionLN_vectorlEROOTcLcLTSchemaHelpercOallocatorlEROOTcLcLTSchemaHelpergRsPgR);
   G__get_linked_tagnum_fwd(&G__G_FiducialVolumeDefinitionLN_reverse_iteratorlEvectorlEROOTcLcLTSchemaHelpercOallocatorlEROOTcLcLTSchemaHelpergRsPgRcLcLiteratorgR);
   G__get_linked_tagnum_fwd(&G__G_FiducialVolumeDefinitionLN_vectorlETVirtualArraymUcOallocatorlETVirtualArraymUgRsPgR);
   G__get_linked_tagnum_fwd(&G__G_FiducialVolumeDefinitionLN_reverse_iteratorlEvectorlETVirtualArraymUcOallocatorlETVirtualArraymUgRsPgRcLcLiteratorgR);
   G__get_linked_tagnum_fwd(&G__G_FiducialVolumeDefinitionLN_TMatrixTBaselEfloatgR);
   G__get_linked_tagnum_fwd(&G__G_FiducialVolumeDefinitionLN_TMatrixTBaselEdoublegR);
   G__get_linked_tagnum_fwd(&G__G_FiducialVolumeDefinitionLN_TVectorTlEfloatgR);
   G__get_linked_tagnum_fwd(&G__G_FiducialVolumeDefinitionLN_TVectorTlEdoublegR);
   G__get_linked_tagnum_fwd(&G__G_FiducialVolumeDefinitionLN_TElementActionTlEfloatgR);
   G__get_linked_tagnum_fwd(&G__G_FiducialVolumeDefinitionLN_TElementPosActionTlEfloatgR);
   G__get_linked_tagnum_fwd(&G__G_FiducialVolumeDefinitionLN_TMatrixTlEfloatgR);
   G__get_linked_tagnum_fwd(&G__G_FiducialVolumeDefinitionLN_TMatrixTRow_constlEfloatgR);
   G__get_linked_tagnum_fwd(&G__G_FiducialVolumeDefinitionLN_TMatrixTRowlEfloatgR);
   G__get_linked_tagnum_fwd(&G__G_FiducialVolumeDefinitionLN_TMatrixTDiag_constlEfloatgR);
   G__get_linked_tagnum_fwd(&G__G_FiducialVolumeDefinitionLN_TMatrixTColumn_constlEfloatgR);
   G__get_linked_tagnum_fwd(&G__G_FiducialVolumeDefinitionLN_TMatrixTFlat_constlEfloatgR);
   G__get_linked_tagnum_fwd(&G__G_FiducialVolumeDefinitionLN_TMatrixTSub_constlEfloatgR);
   G__get_linked_tagnum_fwd(&G__G_FiducialVolumeDefinitionLN_TMatrixTSparseRow_constlEfloatgR);
   G__get_linked_tagnum_fwd(&G__G_FiducialVolumeDefinitionLN_TMatrixTSparseDiag_constlEfloatgR);
   G__get_linked_tagnum_fwd(&G__G_FiducialVolumeDefinitionLN_TMatrixTColumnlEfloatgR);
   G__get_linked_tagnum_fwd(&G__G_FiducialVolumeDefinitionLN_TMatrixTDiaglEfloatgR);
   G__get_linked_tagnum_fwd(&G__G_FiducialVolumeDefinitionLN_TMatrixTFlatlEfloatgR);
   G__get_linked_tagnum_fwd(&G__G_FiducialVolumeDefinitionLN_TMatrixTSublEfloatgR);
   G__get_linked_tagnum_fwd(&G__G_FiducialVolumeDefinitionLN_TMatrixTSparseRowlEfloatgR);
   G__get_linked_tagnum_fwd(&G__G_FiducialVolumeDefinitionLN_TMatrixTSparseDiaglEfloatgR);
   G__tagtable_setup(G__get_linked_tagnum_fwd(&G__G_FiducialVolumeDefinitionLN_FVDef),0,-1,0,(char*)NULL,G__setup_memvarFVDef,G__setup_memfuncFVDef);
}
extern "C" void G__cpp_setupG_FiducialVolumeDefinition(void) {
  G__check_setup_version(30051515,"G__cpp_setupG_FiducialVolumeDefinition()");
  G__set_cpp_environmentG_FiducialVolumeDefinition();
  G__cpp_setup_tagtableG_FiducialVolumeDefinition();

  G__cpp_setup_inheritanceG_FiducialVolumeDefinition();

  G__cpp_setup_typetableG_FiducialVolumeDefinition();

  G__cpp_setup_memvarG_FiducialVolumeDefinition();

  G__cpp_setup_memfuncG_FiducialVolumeDefinition();
  G__cpp_setup_globalG_FiducialVolumeDefinition();
  G__cpp_setup_funcG_FiducialVolumeDefinition();

   if(0==G__getsizep2memfunc()) G__get_sizep2memfuncG_FiducialVolumeDefinition();
  return;
}
class G__cpp_setup_initG_FiducialVolumeDefinition {
  public:
    G__cpp_setup_initG_FiducialVolumeDefinition() { G__add_setup_func("G_FiducialVolumeDefinition",(G__incsetup)(&G__cpp_setupG_FiducialVolumeDefinition)); G__call_setup_funcs(); }
   ~G__cpp_setup_initG_FiducialVolumeDefinition() { G__remove_setup_func("G_FiducialVolumeDefinition"); }
};
G__cpp_setup_initG_FiducialVolumeDefinition G__cpp_setup_initializerG_FiducialVolumeDefinition;

