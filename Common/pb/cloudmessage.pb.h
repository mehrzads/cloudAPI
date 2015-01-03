// Generated by the protocol buffer compiler.  DO NOT EDIT!
// source: cloudmessage.proto

#ifndef PROTOBUF_cloudmessage_2eproto__INCLUDED
#define PROTOBUF_cloudmessage_2eproto__INCLUDED

#include <string>

#include <google/protobuf/stubs/common.h>

#if GOOGLE_PROTOBUF_VERSION < 3000000
#error This file was generated by a newer version of protoc which is
#error incompatible with your Protocol Buffer headers.  Please update
#error your headers.
#endif
#if 3000000 < GOOGLE_PROTOBUF_MIN_PROTOC_VERSION
#error This file was generated by an older version of protoc which is
#error incompatible with your Protocol Buffer headers.  Please
#error regenerate this file with a newer version of protoc.
#endif

#include <google/protobuf/arena.h>
#include <google/protobuf/arenastring.h>
#include <google/protobuf/generated_message_util.h>
#include <google/protobuf/metadata.h>
#include <google/protobuf/message.h>
#include <google/protobuf/repeated_field.h>
#include <google/protobuf/extension_set.h>
#include <google/protobuf/unknown_field_set.h>
// @@protoc_insertion_point(includes)

namespace cloudmessaging {

// Internal implementation detail -- do not call these.
void protobuf_AddDesc_cloudmessage_2eproto();
void protobuf_AssignDesc_cloudmessage_2eproto();
void protobuf_ShutdownFile_cloudmessage_2eproto();

class CommonMessage;
class SizeMessage;
class PointerMessage;
class TransferMessage;

// ===================================================================

class CommonMessage : public ::google::protobuf::Message {
 public:
  CommonMessage();
  virtual ~CommonMessage();

  CommonMessage(const CommonMessage& from);

  inline CommonMessage& operator=(const CommonMessage& from) {
    CopyFrom(from);
    return *this;
  }

  inline const ::google::protobuf::UnknownFieldSet& unknown_fields() const {
    return _internal_metadata_.unknown_fields();
  }

  inline ::google::protobuf::UnknownFieldSet* mutable_unknown_fields() {
    return _internal_metadata_.mutable_unknown_fields();
  }

  static const ::google::protobuf::Descriptor* descriptor();
  static const CommonMessage& default_instance();

  void Swap(CommonMessage* other);

  // implements Message ----------------------------------------------

  inline CommonMessage* New() const { return New(NULL); }

  CommonMessage* New(::google::protobuf::Arena* arena) const;
  void CopyFrom(const ::google::protobuf::Message& from);
  void MergeFrom(const ::google::protobuf::Message& from);
  void CopyFrom(const CommonMessage& from);
  void MergeFrom(const CommonMessage& from);
  void Clear();
  bool IsInitialized() const;

  int ByteSize() const;
  bool MergePartialFromCodedStream(
      ::google::protobuf::io::CodedInputStream* input);
  void SerializeWithCachedSizes(
      ::google::protobuf::io::CodedOutputStream* output) const;
  ::google::protobuf::uint8* SerializeWithCachedSizesToArray(::google::protobuf::uint8* output) const;
  int GetCachedSize() const { return _cached_size_; }
  private:
  void SharedCtor();
  void SharedDtor();
  void SetCachedSize(int size) const;
  void InternalSwap(CommonMessage* other);
  private:
  inline ::google::protobuf::Arena* GetArenaNoVirtual() const {
    return _internal_metadata_.arena();
  }
  inline void* MaybeArenaPtr() const {
    return _internal_metadata_.raw_arena_ptr();
  }
  public:

  ::google::protobuf::Metadata GetMetadata() const;

  // nested types ----------------------------------------------------

  // accessors -------------------------------------------------------

  // required int32 messagetype = 1;
  inline bool has_messagetype() const;
  inline void clear_messagetype();
  static const int kMessagetypeFieldNumber = 1;
  inline ::google::protobuf::int32 messagetype() const;
  inline void set_messagetype(::google::protobuf::int32 value);

  // @@protoc_insertion_point(class_scope:cloudmessaging.CommonMessage)
 private:
  inline void set_has_messagetype();
  inline void clear_has_messagetype();

  ::google::protobuf::internal::InternalMetadataWithArena _internal_metadata_;
  ::google::protobuf::uint32 _has_bits_[1];
  mutable int _cached_size_;
  ::google::protobuf::int32 messagetype_;
  friend void  protobuf_AddDesc_cloudmessage_2eproto();
  friend void protobuf_AssignDesc_cloudmessage_2eproto();
  friend void protobuf_ShutdownFile_cloudmessage_2eproto();

  void InitAsDefaultInstance();
  static CommonMessage* default_instance_;
};
// -------------------------------------------------------------------

class SizeMessage : public ::google::protobuf::Message {
 public:
  SizeMessage();
  virtual ~SizeMessage();

  SizeMessage(const SizeMessage& from);

  inline SizeMessage& operator=(const SizeMessage& from) {
    CopyFrom(from);
    return *this;
  }

  inline const ::google::protobuf::UnknownFieldSet& unknown_fields() const {
    return _internal_metadata_.unknown_fields();
  }

  inline ::google::protobuf::UnknownFieldSet* mutable_unknown_fields() {
    return _internal_metadata_.mutable_unknown_fields();
  }

  static const ::google::protobuf::Descriptor* descriptor();
  static const SizeMessage& default_instance();

  void Swap(SizeMessage* other);

  // implements Message ----------------------------------------------

  inline SizeMessage* New() const { return New(NULL); }

  SizeMessage* New(::google::protobuf::Arena* arena) const;
  void CopyFrom(const ::google::protobuf::Message& from);
  void MergeFrom(const ::google::protobuf::Message& from);
  void CopyFrom(const SizeMessage& from);
  void MergeFrom(const SizeMessage& from);
  void Clear();
  bool IsInitialized() const;

  int ByteSize() const;
  bool MergePartialFromCodedStream(
      ::google::protobuf::io::CodedInputStream* input);
  void SerializeWithCachedSizes(
      ::google::protobuf::io::CodedOutputStream* output) const;
  ::google::protobuf::uint8* SerializeWithCachedSizesToArray(::google::protobuf::uint8* output) const;
  int GetCachedSize() const { return _cached_size_; }
  private:
  void SharedCtor();
  void SharedDtor();
  void SetCachedSize(int size) const;
  void InternalSwap(SizeMessage* other);
  private:
  inline ::google::protobuf::Arena* GetArenaNoVirtual() const {
    return _internal_metadata_.arena();
  }
  inline void* MaybeArenaPtr() const {
    return _internal_metadata_.raw_arena_ptr();
  }
  public:

  ::google::protobuf::Metadata GetMetadata() const;

  // nested types ----------------------------------------------------

  // accessors -------------------------------------------------------

  // required int32 messagetype = 1;
  inline bool has_messagetype() const;
  inline void clear_messagetype();
  static const int kMessagetypeFieldNumber = 1;
  inline ::google::protobuf::int32 messagetype() const;
  inline void set_messagetype(::google::protobuf::int32 value);

  // required int32 size = 2;
  inline bool has_size() const;
  inline void clear_size();
  static const int kSizeFieldNumber = 2;
  inline ::google::protobuf::int32 size() const;
  inline void set_size(::google::protobuf::int32 value);

  // @@protoc_insertion_point(class_scope:cloudmessaging.SizeMessage)
 private:
  inline void set_has_messagetype();
  inline void clear_has_messagetype();
  inline void set_has_size();
  inline void clear_has_size();

  // helper for ByteSize()
  int RequiredFieldsByteSizeFallback() const;

  ::google::protobuf::internal::InternalMetadataWithArena _internal_metadata_;
  ::google::protobuf::uint32 _has_bits_[1];
  mutable int _cached_size_;
  ::google::protobuf::int32 messagetype_;
  ::google::protobuf::int32 size_;
  friend void  protobuf_AddDesc_cloudmessage_2eproto();
  friend void protobuf_AssignDesc_cloudmessage_2eproto();
  friend void protobuf_ShutdownFile_cloudmessage_2eproto();

  void InitAsDefaultInstance();
  static SizeMessage* default_instance_;
};
// -------------------------------------------------------------------

class PointerMessage : public ::google::protobuf::Message {
 public:
  PointerMessage();
  virtual ~PointerMessage();

  PointerMessage(const PointerMessage& from);

  inline PointerMessage& operator=(const PointerMessage& from) {
    CopyFrom(from);
    return *this;
  }

  inline const ::google::protobuf::UnknownFieldSet& unknown_fields() const {
    return _internal_metadata_.unknown_fields();
  }

  inline ::google::protobuf::UnknownFieldSet* mutable_unknown_fields() {
    return _internal_metadata_.mutable_unknown_fields();
  }

  static const ::google::protobuf::Descriptor* descriptor();
  static const PointerMessage& default_instance();

  void Swap(PointerMessage* other);

  // implements Message ----------------------------------------------

  inline PointerMessage* New() const { return New(NULL); }

  PointerMessage* New(::google::protobuf::Arena* arena) const;
  void CopyFrom(const ::google::protobuf::Message& from);
  void MergeFrom(const ::google::protobuf::Message& from);
  void CopyFrom(const PointerMessage& from);
  void MergeFrom(const PointerMessage& from);
  void Clear();
  bool IsInitialized() const;

  int ByteSize() const;
  bool MergePartialFromCodedStream(
      ::google::protobuf::io::CodedInputStream* input);
  void SerializeWithCachedSizes(
      ::google::protobuf::io::CodedOutputStream* output) const;
  ::google::protobuf::uint8* SerializeWithCachedSizesToArray(::google::protobuf::uint8* output) const;
  int GetCachedSize() const { return _cached_size_; }
  private:
  void SharedCtor();
  void SharedDtor();
  void SetCachedSize(int size) const;
  void InternalSwap(PointerMessage* other);
  private:
  inline ::google::protobuf::Arena* GetArenaNoVirtual() const {
    return _internal_metadata_.arena();
  }
  inline void* MaybeArenaPtr() const {
    return _internal_metadata_.raw_arena_ptr();
  }
  public:

  ::google::protobuf::Metadata GetMetadata() const;

  // nested types ----------------------------------------------------

  // accessors -------------------------------------------------------

  // required int32 messagetype = 1;
  inline bool has_messagetype() const;
  inline void clear_messagetype();
  static const int kMessagetypeFieldNumber = 1;
  inline ::google::protobuf::int32 messagetype() const;
  inline void set_messagetype(::google::protobuf::int32 value);

  // required int64 pointer = 2;
  inline bool has_pointer() const;
  inline void clear_pointer();
  static const int kPointerFieldNumber = 2;
  inline ::google::protobuf::int64 pointer() const;
  inline void set_pointer(::google::protobuf::int64 value);

  // @@protoc_insertion_point(class_scope:cloudmessaging.PointerMessage)
 private:
  inline void set_has_messagetype();
  inline void clear_has_messagetype();
  inline void set_has_pointer();
  inline void clear_has_pointer();

  // helper for ByteSize()
  int RequiredFieldsByteSizeFallback() const;

  ::google::protobuf::internal::InternalMetadataWithArena _internal_metadata_;
  ::google::protobuf::uint32 _has_bits_[1];
  mutable int _cached_size_;
  ::google::protobuf::int64 pointer_;
  ::google::protobuf::int32 messagetype_;
  friend void  protobuf_AddDesc_cloudmessage_2eproto();
  friend void protobuf_AssignDesc_cloudmessage_2eproto();
  friend void protobuf_ShutdownFile_cloudmessage_2eproto();

  void InitAsDefaultInstance();
  static PointerMessage* default_instance_;
};
// -------------------------------------------------------------------

class TransferMessage : public ::google::protobuf::Message {
 public:
  TransferMessage();
  virtual ~TransferMessage();

  TransferMessage(const TransferMessage& from);

  inline TransferMessage& operator=(const TransferMessage& from) {
    CopyFrom(from);
    return *this;
  }

  inline const ::google::protobuf::UnknownFieldSet& unknown_fields() const {
    return _internal_metadata_.unknown_fields();
  }

  inline ::google::protobuf::UnknownFieldSet* mutable_unknown_fields() {
    return _internal_metadata_.mutable_unknown_fields();
  }

  static const ::google::protobuf::Descriptor* descriptor();
  static const TransferMessage& default_instance();

  void Swap(TransferMessage* other);

  // implements Message ----------------------------------------------

  inline TransferMessage* New() const { return New(NULL); }

  TransferMessage* New(::google::protobuf::Arena* arena) const;
  void CopyFrom(const ::google::protobuf::Message& from);
  void MergeFrom(const ::google::protobuf::Message& from);
  void CopyFrom(const TransferMessage& from);
  void MergeFrom(const TransferMessage& from);
  void Clear();
  bool IsInitialized() const;

  int ByteSize() const;
  bool MergePartialFromCodedStream(
      ::google::protobuf::io::CodedInputStream* input);
  void SerializeWithCachedSizes(
      ::google::protobuf::io::CodedOutputStream* output) const;
  ::google::protobuf::uint8* SerializeWithCachedSizesToArray(::google::protobuf::uint8* output) const;
  int GetCachedSize() const { return _cached_size_; }
  private:
  void SharedCtor();
  void SharedDtor();
  void SetCachedSize(int size) const;
  void InternalSwap(TransferMessage* other);
  private:
  inline ::google::protobuf::Arena* GetArenaNoVirtual() const {
    return _internal_metadata_.arena();
  }
  inline void* MaybeArenaPtr() const {
    return _internal_metadata_.raw_arena_ptr();
  }
  public:

  ::google::protobuf::Metadata GetMetadata() const;

  // nested types ----------------------------------------------------

  // accessors -------------------------------------------------------

  // required int32 messagetype = 1;
  inline bool has_messagetype() const;
  inline void clear_messagetype();
  static const int kMessagetypeFieldNumber = 1;
  inline ::google::protobuf::int32 messagetype() const;
  inline void set_messagetype(::google::protobuf::int32 value);

  // required int32 compresskind = 2;
  inline bool has_compresskind() const;
  inline void clear_compresskind();
  static const int kCompresskindFieldNumber = 2;
  inline ::google::protobuf::int32 compresskind() const;
  inline void set_compresskind(::google::protobuf::int32 value);

  // required int32 size = 3;
  inline bool has_size() const;
  inline void clear_size();
  static const int kSizeFieldNumber = 3;
  inline ::google::protobuf::int32 size() const;
  inline void set_size(::google::protobuf::int32 value);

  // required int32 compressedsize = 4;
  inline bool has_compressedsize() const;
  inline void clear_compressedsize();
  static const int kCompressedsizeFieldNumber = 4;
  inline ::google::protobuf::int32 compressedsize() const;
  inline void set_compressedsize(::google::protobuf::int32 value);

  // required int64 pointer = 5;
  inline bool has_pointer() const;
  inline void clear_pointer();
  static const int kPointerFieldNumber = 5;
  inline ::google::protobuf::int64 pointer() const;
  inline void set_pointer(::google::protobuf::int64 value);

  // @@protoc_insertion_point(class_scope:cloudmessaging.TransferMessage)
 private:
  inline void set_has_messagetype();
  inline void clear_has_messagetype();
  inline void set_has_compresskind();
  inline void clear_has_compresskind();
  inline void set_has_size();
  inline void clear_has_size();
  inline void set_has_compressedsize();
  inline void clear_has_compressedsize();
  inline void set_has_pointer();
  inline void clear_has_pointer();

  // helper for ByteSize()
  int RequiredFieldsByteSizeFallback() const;

  ::google::protobuf::internal::InternalMetadataWithArena _internal_metadata_;
  ::google::protobuf::uint32 _has_bits_[1];
  mutable int _cached_size_;
  ::google::protobuf::int32 messagetype_;
  ::google::protobuf::int32 compresskind_;
  ::google::protobuf::int32 size_;
  ::google::protobuf::int32 compressedsize_;
  ::google::protobuf::int64 pointer_;
  friend void  protobuf_AddDesc_cloudmessage_2eproto();
  friend void protobuf_AssignDesc_cloudmessage_2eproto();
  friend void protobuf_ShutdownFile_cloudmessage_2eproto();

  void InitAsDefaultInstance();
  static TransferMessage* default_instance_;
};
// ===================================================================


// ===================================================================

// CommonMessage

// required int32 messagetype = 1;
inline bool CommonMessage::has_messagetype() const {
  return (_has_bits_[0] & 0x00000001u) != 0;
}
inline void CommonMessage::set_has_messagetype() {
  _has_bits_[0] |= 0x00000001u;
}
inline void CommonMessage::clear_has_messagetype() {
  _has_bits_[0] &= ~0x00000001u;
}
inline void CommonMessage::clear_messagetype() {
  messagetype_ = 0;
  clear_has_messagetype();
}
inline ::google::protobuf::int32 CommonMessage::messagetype() const {
  // @@protoc_insertion_point(field_get:cloudmessaging.CommonMessage.messagetype)
  return messagetype_;
}
inline void CommonMessage::set_messagetype(::google::protobuf::int32 value) {
  set_has_messagetype();
  messagetype_ = value;
  // @@protoc_insertion_point(field_set:cloudmessaging.CommonMessage.messagetype)
}

// -------------------------------------------------------------------

// SizeMessage

// required int32 messagetype = 1;
inline bool SizeMessage::has_messagetype() const {
  return (_has_bits_[0] & 0x00000001u) != 0;
}
inline void SizeMessage::set_has_messagetype() {
  _has_bits_[0] |= 0x00000001u;
}
inline void SizeMessage::clear_has_messagetype() {
  _has_bits_[0] &= ~0x00000001u;
}
inline void SizeMessage::clear_messagetype() {
  messagetype_ = 0;
  clear_has_messagetype();
}
inline ::google::protobuf::int32 SizeMessage::messagetype() const {
  // @@protoc_insertion_point(field_get:cloudmessaging.SizeMessage.messagetype)
  return messagetype_;
}
inline void SizeMessage::set_messagetype(::google::protobuf::int32 value) {
  set_has_messagetype();
  messagetype_ = value;
  // @@protoc_insertion_point(field_set:cloudmessaging.SizeMessage.messagetype)
}

// required int32 size = 2;
inline bool SizeMessage::has_size() const {
  return (_has_bits_[0] & 0x00000002u) != 0;
}
inline void SizeMessage::set_has_size() {
  _has_bits_[0] |= 0x00000002u;
}
inline void SizeMessage::clear_has_size() {
  _has_bits_[0] &= ~0x00000002u;
}
inline void SizeMessage::clear_size() {
  size_ = 0;
  clear_has_size();
}
inline ::google::protobuf::int32 SizeMessage::size() const {
  // @@protoc_insertion_point(field_get:cloudmessaging.SizeMessage.size)
  return size_;
}
inline void SizeMessage::set_size(::google::protobuf::int32 value) {
  set_has_size();
  size_ = value;
  // @@protoc_insertion_point(field_set:cloudmessaging.SizeMessage.size)
}

// -------------------------------------------------------------------

// PointerMessage

// required int32 messagetype = 1;
inline bool PointerMessage::has_messagetype() const {
  return (_has_bits_[0] & 0x00000001u) != 0;
}
inline void PointerMessage::set_has_messagetype() {
  _has_bits_[0] |= 0x00000001u;
}
inline void PointerMessage::clear_has_messagetype() {
  _has_bits_[0] &= ~0x00000001u;
}
inline void PointerMessage::clear_messagetype() {
  messagetype_ = 0;
  clear_has_messagetype();
}
inline ::google::protobuf::int32 PointerMessage::messagetype() const {
  // @@protoc_insertion_point(field_get:cloudmessaging.PointerMessage.messagetype)
  return messagetype_;
}
inline void PointerMessage::set_messagetype(::google::protobuf::int32 value) {
  set_has_messagetype();
  messagetype_ = value;
  // @@protoc_insertion_point(field_set:cloudmessaging.PointerMessage.messagetype)
}

// required int64 pointer = 2;
inline bool PointerMessage::has_pointer() const {
  return (_has_bits_[0] & 0x00000002u) != 0;
}
inline void PointerMessage::set_has_pointer() {
  _has_bits_[0] |= 0x00000002u;
}
inline void PointerMessage::clear_has_pointer() {
  _has_bits_[0] &= ~0x00000002u;
}
inline void PointerMessage::clear_pointer() {
  pointer_ = GOOGLE_LONGLONG(0);
  clear_has_pointer();
}
inline ::google::protobuf::int64 PointerMessage::pointer() const {
  // @@protoc_insertion_point(field_get:cloudmessaging.PointerMessage.pointer)
  return pointer_;
}
inline void PointerMessage::set_pointer(::google::protobuf::int64 value) {
  set_has_pointer();
  pointer_ = value;
  // @@protoc_insertion_point(field_set:cloudmessaging.PointerMessage.pointer)
}

// -------------------------------------------------------------------

// TransferMessage

// required int32 messagetype = 1;
inline bool TransferMessage::has_messagetype() const {
  return (_has_bits_[0] & 0x00000001u) != 0;
}
inline void TransferMessage::set_has_messagetype() {
  _has_bits_[0] |= 0x00000001u;
}
inline void TransferMessage::clear_has_messagetype() {
  _has_bits_[0] &= ~0x00000001u;
}
inline void TransferMessage::clear_messagetype() {
  messagetype_ = 0;
  clear_has_messagetype();
}
inline ::google::protobuf::int32 TransferMessage::messagetype() const {
  // @@protoc_insertion_point(field_get:cloudmessaging.TransferMessage.messagetype)
  return messagetype_;
}
inline void TransferMessage::set_messagetype(::google::protobuf::int32 value) {
  set_has_messagetype();
  messagetype_ = value;
  // @@protoc_insertion_point(field_set:cloudmessaging.TransferMessage.messagetype)
}

// required int32 compresskind = 2;
inline bool TransferMessage::has_compresskind() const {
  return (_has_bits_[0] & 0x00000002u) != 0;
}
inline void TransferMessage::set_has_compresskind() {
  _has_bits_[0] |= 0x00000002u;
}
inline void TransferMessage::clear_has_compresskind() {
  _has_bits_[0] &= ~0x00000002u;
}
inline void TransferMessage::clear_compresskind() {
  compresskind_ = 0;
  clear_has_compresskind();
}
inline ::google::protobuf::int32 TransferMessage::compresskind() const {
  // @@protoc_insertion_point(field_get:cloudmessaging.TransferMessage.compresskind)
  return compresskind_;
}
inline void TransferMessage::set_compresskind(::google::protobuf::int32 value) {
  set_has_compresskind();
  compresskind_ = value;
  // @@protoc_insertion_point(field_set:cloudmessaging.TransferMessage.compresskind)
}

// required int32 size = 3;
inline bool TransferMessage::has_size() const {
  return (_has_bits_[0] & 0x00000004u) != 0;
}
inline void TransferMessage::set_has_size() {
  _has_bits_[0] |= 0x00000004u;
}
inline void TransferMessage::clear_has_size() {
  _has_bits_[0] &= ~0x00000004u;
}
inline void TransferMessage::clear_size() {
  size_ = 0;
  clear_has_size();
}
inline ::google::protobuf::int32 TransferMessage::size() const {
  // @@protoc_insertion_point(field_get:cloudmessaging.TransferMessage.size)
  return size_;
}
inline void TransferMessage::set_size(::google::protobuf::int32 value) {
  set_has_size();
  size_ = value;
  // @@protoc_insertion_point(field_set:cloudmessaging.TransferMessage.size)
}

// required int32 compressedsize = 4;
inline bool TransferMessage::has_compressedsize() const {
  return (_has_bits_[0] & 0x00000008u) != 0;
}
inline void TransferMessage::set_has_compressedsize() {
  _has_bits_[0] |= 0x00000008u;
}
inline void TransferMessage::clear_has_compressedsize() {
  _has_bits_[0] &= ~0x00000008u;
}
inline void TransferMessage::clear_compressedsize() {
  compressedsize_ = 0;
  clear_has_compressedsize();
}
inline ::google::protobuf::int32 TransferMessage::compressedsize() const {
  // @@protoc_insertion_point(field_get:cloudmessaging.TransferMessage.compressedsize)
  return compressedsize_;
}
inline void TransferMessage::set_compressedsize(::google::protobuf::int32 value) {
  set_has_compressedsize();
  compressedsize_ = value;
  // @@protoc_insertion_point(field_set:cloudmessaging.TransferMessage.compressedsize)
}

// required int64 pointer = 5;
inline bool TransferMessage::has_pointer() const {
  return (_has_bits_[0] & 0x00000010u) != 0;
}
inline void TransferMessage::set_has_pointer() {
  _has_bits_[0] |= 0x00000010u;
}
inline void TransferMessage::clear_has_pointer() {
  _has_bits_[0] &= ~0x00000010u;
}
inline void TransferMessage::clear_pointer() {
  pointer_ = GOOGLE_LONGLONG(0);
  clear_has_pointer();
}
inline ::google::protobuf::int64 TransferMessage::pointer() const {
  // @@protoc_insertion_point(field_get:cloudmessaging.TransferMessage.pointer)
  return pointer_;
}
inline void TransferMessage::set_pointer(::google::protobuf::int64 value) {
  set_has_pointer();
  pointer_ = value;
  // @@protoc_insertion_point(field_set:cloudmessaging.TransferMessage.pointer)
}


// @@protoc_insertion_point(namespace_scope)

}  // namespace cloudmessaging

#ifndef SWIG
namespace google {
namespace protobuf {


}  // namespace protobuf
}  // namespace google
#endif  // SWIG

// @@protoc_insertion_point(global_scope)

#endif  // PROTOBUF_cloudmessage_2eproto__INCLUDED
