//===--- Demangle.h - Interface to Swift symbol demangling -------*- C++ -*-==//
//
// This source file is part of the Swift.org open source project
//
// Copyright (c) 2014 - 2015 Apple Inc. and the Swift project authors
// Licensed under Apache License v2.0 with Runtime Library Exception
//
// See http://swift.org/LICENSE.txt for license information
// See http://swift.org/CONTRIBUTORS.txt for the list of Swift project authors
//
//===----------------------------------------------------------------------===//

#ifndef SWIFT_BASIC_DEMANGLE_H
#define SWIFT_BASIC_DEMANGLE_H

#include "llvm/ADT/IntrusiveRefCntPtr.h"
#include "llvm/ADT/SmallVector.h"
#include "llvm/ADT/StringRef.h"
#include "swift/Basic/LLVM.h"

namespace swift {
namespace Demangle {

class Node;
typedef llvm::IntrusiveRefCntPtr<Node> NodePointer;

class Node : public llvm::RefCountedBase<Node> {
public:
  typedef llvm::SmallVector<NodePointer, 10> ChildNodes;
  typedef ChildNodes::iterator iterator;
  typedef ChildNodes::const_iterator const_iterator;
  typedef ChildNodes::size_type size_type;

  enum class Kind {
    Failure = 0,
    Module,
    Class,
    Structure,
    Union,
    Protocol,
    Substitution,
    TypeName,
    MetaType,
    ReturnType,
    Constructor,
    Destructor,
    BaseName,
    ObjCAttribute,
    Directness,
    GenericTypeMetadataPattern,
    ProtocolWitness,
    Metaclass,
    TypeMetadata,
    ArrayType,
    Number,
    BuiltinTypeName,
    FunctionType,
    UncurriedFunctionType,
    UncurriedFunctionMetaType,
    UncurriedFunctionFunctionType,
    ObjCBlock,
    GenericTypeApplication,
    TypeList,
    ArgumentTuple,
    ValueWitnessKind,
    ValueWitnessTable,
    WitnessTableOffset,
    FieldOffset,
    ProtocolWitnessTable,
    LazyProtocolWitnessTableAccessor,
    LazyProtocolWitnessTableTemplate,
    DependentProtocolWitnessTableGenerator,
    DependentProtocolWitnessTableTemplate,
    BridgeToBlockFunction,
    ProtocolConformance,
    PrefixOperator,
    PostfixOperator,
    InfixOperator,
    Identifier,
    DeclIdentifier,
    LocalEntity,
    Deallocator,
    Allocator,
    Declaration,
    Addressor,
    Getter,
    Setter,
    VariadicTuple,
    NonVariadicTuple,
    TupleElement,
    ProtocolList,
    ArchetypeRef,
    ArchetypeAndProtocol,
    ArchetypeList,
    ByRef,
    GenericType,
    Unowned,
    Weak,
    Unknown,
    TupleElementName,
    TupleElementType,
    TypeListEntry,
    FunctionName,
    NominalType
  };

  Node(Kind k, std::string t = "");
  
  Node (const Node& other);

  llvm::StringRef getText();
  void setText(std::string t);

  Kind getKind();
  void setKind(Kind k);

  NodePointer getNextNode();
  NodePointer setNextNode(NodePointer n);

  NodePointer push_back_child(NodePointer c);

  NodePointer child_at(size_type pos);

  NodePointer front();
  NodePointer back();
  
  iterator begin();
  iterator end();

  const_iterator begin() const;
  const_iterator end() const;

  size_type size();

  static NodePointer makeNodePointer(Kind k, std::string t = "");

private:
  Node *ParentNode;
  std::string TextContent;
  Kind NodeKind;
  NodePointer NextNode;
  ChildNodes Children;
};

/// \brief Demangle the given string as a Swift symbol.
///
/// Typical usage:
/// \code
///   NodePointer aDemangledName =
/// swift::Demangler::demangleSymbol("SomeSwiftMangledName")
/// \endcode
///
/// \param mangled The mangled string.
///
///
/// \returns A parse tree for the demangled string - or a Failure node on
/// failure.
///
NodePointer demangleSymbolAsNode(llvm::StringRef mangled);

/// \brief Transform the node structure in a string.
///
/// Typical usage:
/// \code
///   std::string aDemangledName =
/// swift::Demangler::nodeToString(aNode)
/// \endcode
///
/// \param pointer A pointer to a parse tree generated by the demangler.
///
///
/// \returns A string representing the demangled name.
///
std::string nodeToString(NodePointer pointer);

/// \brief Demangle the given string as a Swift symbol.
///
/// Typical usage:
/// \code
///   std::string aDemangledName =
/// swift::Demangler::demangleSymbol("SomeSwiftMangledName")
/// \endcode
///
/// \param mangled The mangled string.
///
///
/// \returns A string representing the demangled name.
///
std::string demangleSymbolAsString(llvm::StringRef mangled);

} // end namespace Demangle
} // end namespace swift

#endif
