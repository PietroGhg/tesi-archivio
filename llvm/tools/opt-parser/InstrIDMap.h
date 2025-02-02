#pragma once
#include <map>
#include "llvm/ADT/SmallVector.h"
#include "llvm/IR/Instruction.h"
#include "llvm/IR/Module.h"
#include "Log.h"

using namespace std;
using namespace llvm;

using InstrIDMap_t = map<Instruction*, unsigned long>;
using IDInstrMap_t = map<unsigned long, vector<Instruction*>>;
using InstrEntryMap_t = map<Instruction*, vector<Entry>>;

inline InstrIDMap_t getInstrIDmap(Module* M){
  InstrIDMap_t Res;
  for(auto& F : *M){
    for(auto& BB : F){
      for(auto& I : BB){
	if(I.hasID()){
	  Res[&I] = I.getIDInt();
	}
      }
    }
  }
  return Res;
}

inline IDInstrMap_t getIDInstrMap(Module* M){
  IDInstrMap_t Res;
  for(auto& F : *M){
    for(auto& BB : F){
      for(auto& I : BB){
	if(I.hasID()){
	  Res[I.getIDInt()].push_back(&I);
	}
      }
    }
  }
  return Res;
}

inline void updateIDInstrMap(IDInstrMap_t& Map, Module* M){
  for(auto& F : *M){
    for(auto& BB : F){
      for(auto& I : BB){
	if(I.hasID()){
	  Map[I.getIDInt()].push_back(&I);
	}
      }
    }
  }
}

inline void updateInstEntryMap(Module* M,
			       const Log& L,
			       InstrEntryMap_t& Map){

  IDInstrMap_t IDInstrBefore = getIDInstrMap(M);
  InstrIDMap_t InstrIDIDBefore = getInstrIDmap(M);

  for(auto& Entry : L.getEntries()){
      auto InstrsBefore = IDInstrBefore[Entry.getInstID1()];
      for(Instruction *IBefore : InstrsBefore)
        Map[IBefore].push_back(Entry);	
  }
}
 




 


      


