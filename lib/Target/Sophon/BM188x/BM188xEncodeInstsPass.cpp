//===---------------------------------------------------------------------===//
//
//                             The ONNC Project
//
// Copyright(c) 2018, The ONNC Team
//
// This file is part of the ONNC Project and is distributed under
// 3-clause BSD license (https://opensource.org/licenses/BSD-3-Clause)
//
// See LICENSE.TXT for details.
//
//===---------------------------------------------------------------------===//

#include "BM188xEncodeInstsPass.h"
#include <onnc/IR/Compute/Initializer.h>
#include <onnc/IR/Compute/InputOperator.h>
#include <onnc/IR/Compute/OutputOperator.h>
#include <onnc/Target/Sophon/BM188x/bmkernel_api.h>

using namespace onnc;
using namespace onnc::BM188X;

char BM188xEncodeInsts::ID = 0;

BM188xEncodeInsts::BM188xEncodeInsts(BM188X::CodeEmitVisitor *pInstVisitor,
                                     const std::string &pFilename)
    : EncodeInstructions(pInstVisitor, ID), m_FileName(pFilename)
{
}

Pass::ReturnType BM188xEncodeInsts::runOnModule(::onnc::Module &pModule)
{
  OFStream ofs;
  std::ostream *os;
  if (m_FileName == "-") {
    os = &onnc::outs();
  } else {
    ofs.open(m_FileName + ".s", std::ios::out);
    os = &ofs;
  }
  ::bmnet::bmnet_asm::asm_context::get_context().set_fp(*os);
  return EncodeInstructions::runOnModule(pModule);
}

void BM188xEncodeInsts::beforeEmit(const ::onnc::ComputeOperator *pOp)
{
  if (isa<OutputOperator>(pOp) || isa<InputOperator>(pOp) ||
      isa<Initializer>(pOp))
    return;

  ::bmnet::bmnet_asm::asm_context::get_context().name =
      pOp->getOutput(0)->getName();
}

//===----------------------------------------------------------------------===//
// Factory method
//===----------------------------------------------------------------------===//
ModulePass *BM188X::CreateEncodeInstsPass(BM188X::CodeEmitVisitor *pVisitor,
                                          const std::string &pOutFile)
{
  return new BM188xEncodeInsts(pVisitor, pOutFile);
}
