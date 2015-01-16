// Generated by the protocol buffer compiler.  DO NOT EDIT!
// source: clblasargs.proto

#define INTERNAL_SUPPRESS_PROTOBUF_FIELD_DEPRECATION
#include "clblasargs.pb.h"

#include <algorithm>

#include <google/protobuf/stubs/common.h>
#include <google/protobuf/stubs/once.h>
#include <google/protobuf/io/coded_stream.h>
#include <google/protobuf/wire_format_lite_inl.h>
#include <google/protobuf/descriptor.h>
#include <google/protobuf/generated_message_reflection.h>
#include <google/protobuf/reflection_ops.h>
#include <google/protobuf/wire_format.h>
// @@protoc_insertion_point(includes)

namespace clblasargs {

namespace {

const ::google::protobuf::Descriptor* DGEMMMessage_descriptor_ = NULL;
const ::google::protobuf::internal::GeneratedMessageReflection*
  DGEMMMessage_reflection_ = NULL;

}  // namespace


void protobuf_AssignDesc_clblasargs_2eproto() {
  protobuf_AddDesc_clblasargs_2eproto();
  const ::google::protobuf::FileDescriptor* file =
    ::google::protobuf::DescriptorPool::generated_pool()->FindFileByName(
      "clblasargs.proto");
  GOOGLE_CHECK(file != NULL);
  DGEMMMessage_descriptor_ = file->message_type(0);
  static const int DGEMMMessage_offsets_[14] = {
    GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(DGEMMMessage, order_),
    GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(DGEMMMessage, transa_),
    GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(DGEMMMessage, transb_),
    GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(DGEMMMessage, m_),
    GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(DGEMMMessage, n_),
    GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(DGEMMMessage, k_),
    GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(DGEMMMessage, alpha_),
    GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(DGEMMMessage, a_),
    GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(DGEMMMessage, lda_),
    GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(DGEMMMessage, b_),
    GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(DGEMMMessage, ldb_),
    GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(DGEMMMessage, beta_),
    GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(DGEMMMessage, c_),
    GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(DGEMMMessage, ldc_),
  };
  DGEMMMessage_reflection_ =
    ::google::protobuf::internal::GeneratedMessageReflection::NewGeneratedMessageReflection(
      DGEMMMessage_descriptor_,
      DGEMMMessage::default_instance_,
      DGEMMMessage_offsets_,
      GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(DGEMMMessage, _has_bits_[0]),
      -1,
      -1,
      sizeof(DGEMMMessage),
      GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(DGEMMMessage, _internal_metadata_),
      -1);
}

namespace {

GOOGLE_PROTOBUF_DECLARE_ONCE(protobuf_AssignDescriptors_once_);
inline void protobuf_AssignDescriptorsOnce() {
  ::google::protobuf::GoogleOnceInit(&protobuf_AssignDescriptors_once_,
                 &protobuf_AssignDesc_clblasargs_2eproto);
}

void protobuf_RegisterTypes(const ::std::string&) {
  protobuf_AssignDescriptorsOnce();
  ::google::protobuf::MessageFactory::InternalRegisterGeneratedMessage(
      DGEMMMessage_descriptor_, &DGEMMMessage::default_instance());
}

}  // namespace

void protobuf_ShutdownFile_clblasargs_2eproto() {
  delete DGEMMMessage::default_instance_;
  delete DGEMMMessage_reflection_;
}

void protobuf_AddDesc_clblasargs_2eproto() {
  static bool already_here = false;
  if (already_here) return;
  already_here = true;
  GOOGLE_PROTOBUF_VERIFY_VERSION;

  ::google::protobuf::DescriptorPool::InternalAddGeneratedFile(
    "\n\020clblasargs.proto\022\nclblasargs\"\303\001\n\014DGEMM"
    "Message\022\r\n\005order\030\001 \002(\005\022\016\n\006transA\030\002 \002(\005\022\016"
    "\n\006transB\030\003 \002(\005\022\t\n\001M\030\004 \002(\005\022\t\n\001N\030\005 \002(\005\022\t\n\001"
    "K\030\006 \002(\005\022\r\n\005alpha\030\007 \002(\001\022\t\n\001A\030\010 \002(\003\022\013\n\003lda"
    "\030\t \002(\005\022\t\n\001B\030\n \002(\003\022\013\n\003ldb\030\013 \002(\005\022\014\n\004beta\030\014"
    " \002(\001\022\t\n\001C\030\r \002(\003\022\013\n\003ldc\030\016 \002(\005", 228);
  ::google::protobuf::MessageFactory::InternalRegisterGeneratedFile(
    "clblasargs.proto", &protobuf_RegisterTypes);
  DGEMMMessage::default_instance_ = new DGEMMMessage();
  DGEMMMessage::default_instance_->InitAsDefaultInstance();
  ::google::protobuf::internal::OnShutdown(&protobuf_ShutdownFile_clblasargs_2eproto);
}

// Force AddDescriptors() to be called at static initialization time.
struct StaticDescriptorInitializer_clblasargs_2eproto {
  StaticDescriptorInitializer_clblasargs_2eproto() {
    protobuf_AddDesc_clblasargs_2eproto();
  }
} static_descriptor_initializer_clblasargs_2eproto_;

namespace {

static void MergeFromFail(int line) GOOGLE_ATTRIBUTE_COLD;
static void MergeFromFail(int line) {
  GOOGLE_CHECK(false) << __FILE__ << ":" << line;
}

}  // namespace


// ===================================================================

#ifndef _MSC_VER
const int DGEMMMessage::kOrderFieldNumber;
const int DGEMMMessage::kTransAFieldNumber;
const int DGEMMMessage::kTransBFieldNumber;
const int DGEMMMessage::kMFieldNumber;
const int DGEMMMessage::kNFieldNumber;
const int DGEMMMessage::kKFieldNumber;
const int DGEMMMessage::kAlphaFieldNumber;
const int DGEMMMessage::kAFieldNumber;
const int DGEMMMessage::kLdaFieldNumber;
const int DGEMMMessage::kBFieldNumber;
const int DGEMMMessage::kLdbFieldNumber;
const int DGEMMMessage::kBetaFieldNumber;
const int DGEMMMessage::kCFieldNumber;
const int DGEMMMessage::kLdcFieldNumber;
#endif  // !_MSC_VER

DGEMMMessage::DGEMMMessage()
  : ::google::protobuf::Message() , _internal_metadata_(NULL)  {
  SharedCtor();
  // @@protoc_insertion_point(constructor:clblasargs.DGEMMMessage)
}

void DGEMMMessage::InitAsDefaultInstance() {
}

DGEMMMessage::DGEMMMessage(const DGEMMMessage& from)
  : ::google::protobuf::Message(),
    _internal_metadata_(NULL) {
  SharedCtor();
  MergeFrom(from);
  // @@protoc_insertion_point(copy_constructor:clblasargs.DGEMMMessage)
}

void DGEMMMessage::SharedCtor() {
  _cached_size_ = 0;
  order_ = 0;
  transa_ = 0;
  transb_ = 0;
  m_ = 0;
  n_ = 0;
  k_ = 0;
  alpha_ = 0;
  a_ = GOOGLE_LONGLONG(0);
  lda_ = 0;
  b_ = GOOGLE_LONGLONG(0);
  ldb_ = 0;
  beta_ = 0;
  c_ = GOOGLE_LONGLONG(0);
  ldc_ = 0;
  ::memset(_has_bits_, 0, sizeof(_has_bits_));
}

DGEMMMessage::~DGEMMMessage() {
  // @@protoc_insertion_point(destructor:clblasargs.DGEMMMessage)
  SharedDtor();
}

void DGEMMMessage::SharedDtor() {
  if (this != default_instance_) {
  }
}

void DGEMMMessage::SetCachedSize(int size) const {
  GOOGLE_SAFE_CONCURRENT_WRITES_BEGIN();
  _cached_size_ = size;
  GOOGLE_SAFE_CONCURRENT_WRITES_END();
}
const ::google::protobuf::Descriptor* DGEMMMessage::descriptor() {
  protobuf_AssignDescriptorsOnce();
  return DGEMMMessage_descriptor_;
}

const DGEMMMessage& DGEMMMessage::default_instance() {
  if (default_instance_ == NULL) protobuf_AddDesc_clblasargs_2eproto();
  return *default_instance_;
}

DGEMMMessage* DGEMMMessage::default_instance_ = NULL;

DGEMMMessage* DGEMMMessage::New(::google::protobuf::Arena* arena) const {
  DGEMMMessage* n = new DGEMMMessage;
  if (arena != NULL) {
    arena->Own(n);
  }
  return n;
}

void DGEMMMessage::Clear() {
#define OFFSET_OF_FIELD_(f) (reinterpret_cast<char*>(      \
  &reinterpret_cast<DGEMMMessage*>(16)->f) - \
   reinterpret_cast<char*>(16))

#define ZR_(first, last) do {                              \
    size_t f = OFFSET_OF_FIELD_(first);                    \
    size_t n = OFFSET_OF_FIELD_(last) - f + sizeof(last);  \
    ::memset(&first, 0, n);                                \
  } while (0)

  if (_has_bits_[0 / 32] & 255) {
    ZR_(order_, a_);
  }
  if (_has_bits_[8 / 32] & 16128) {
    ZR_(b_, ldc_);
  }

#undef OFFSET_OF_FIELD_
#undef ZR_

  ::memset(_has_bits_, 0, sizeof(_has_bits_));
  if (_internal_metadata_.have_unknown_fields()) {
    mutable_unknown_fields()->Clear();
  }
}

bool DGEMMMessage::MergePartialFromCodedStream(
    ::google::protobuf::io::CodedInputStream* input) {
#define DO_(EXPRESSION) if (!(EXPRESSION)) goto failure
  ::google::protobuf::uint32 tag;
  // @@protoc_insertion_point(parse_start:clblasargs.DGEMMMessage)
  for (;;) {
    ::std::pair< ::google::protobuf::uint32, bool> p = input->ReadTagWithCutoff(127);
    tag = p.first;
    if (!p.second) goto handle_unusual;
    switch (::google::protobuf::internal::WireFormatLite::GetTagFieldNumber(tag)) {
      // required int32 order = 1;
      case 1: {
        if (tag == 8) {
          DO_((::google::protobuf::internal::WireFormatLite::ReadPrimitive<
                   ::google::protobuf::int32, ::google::protobuf::internal::WireFormatLite::TYPE_INT32>(
                 input, &order_)));
          set_has_order();
        } else {
          goto handle_unusual;
        }
        if (input->ExpectTag(16)) goto parse_transA;
        break;
      }

      // required int32 transA = 2;
      case 2: {
        if (tag == 16) {
         parse_transA:
          DO_((::google::protobuf::internal::WireFormatLite::ReadPrimitive<
                   ::google::protobuf::int32, ::google::protobuf::internal::WireFormatLite::TYPE_INT32>(
                 input, &transa_)));
          set_has_transa();
        } else {
          goto handle_unusual;
        }
        if (input->ExpectTag(24)) goto parse_transB;
        break;
      }

      // required int32 transB = 3;
      case 3: {
        if (tag == 24) {
         parse_transB:
          DO_((::google::protobuf::internal::WireFormatLite::ReadPrimitive<
                   ::google::protobuf::int32, ::google::protobuf::internal::WireFormatLite::TYPE_INT32>(
                 input, &transb_)));
          set_has_transb();
        } else {
          goto handle_unusual;
        }
        if (input->ExpectTag(32)) goto parse_M;
        break;
      }

      // required int32 M = 4;
      case 4: {
        if (tag == 32) {
         parse_M:
          DO_((::google::protobuf::internal::WireFormatLite::ReadPrimitive<
                   ::google::protobuf::int32, ::google::protobuf::internal::WireFormatLite::TYPE_INT32>(
                 input, &m_)));
          set_has_m();
        } else {
          goto handle_unusual;
        }
        if (input->ExpectTag(40)) goto parse_N;
        break;
      }

      // required int32 N = 5;
      case 5: {
        if (tag == 40) {
         parse_N:
          DO_((::google::protobuf::internal::WireFormatLite::ReadPrimitive<
                   ::google::protobuf::int32, ::google::protobuf::internal::WireFormatLite::TYPE_INT32>(
                 input, &n_)));
          set_has_n();
        } else {
          goto handle_unusual;
        }
        if (input->ExpectTag(48)) goto parse_K;
        break;
      }

      // required int32 K = 6;
      case 6: {
        if (tag == 48) {
         parse_K:
          DO_((::google::protobuf::internal::WireFormatLite::ReadPrimitive<
                   ::google::protobuf::int32, ::google::protobuf::internal::WireFormatLite::TYPE_INT32>(
                 input, &k_)));
          set_has_k();
        } else {
          goto handle_unusual;
        }
        if (input->ExpectTag(57)) goto parse_alpha;
        break;
      }

      // required double alpha = 7;
      case 7: {
        if (tag == 57) {
         parse_alpha:
          DO_((::google::protobuf::internal::WireFormatLite::ReadPrimitive<
                   double, ::google::protobuf::internal::WireFormatLite::TYPE_DOUBLE>(
                 input, &alpha_)));
          set_has_alpha();
        } else {
          goto handle_unusual;
        }
        if (input->ExpectTag(64)) goto parse_A;
        break;
      }

      // required int64 A = 8;
      case 8: {
        if (tag == 64) {
         parse_A:
          DO_((::google::protobuf::internal::WireFormatLite::ReadPrimitive<
                   ::google::protobuf::int64, ::google::protobuf::internal::WireFormatLite::TYPE_INT64>(
                 input, &a_)));
          set_has_a();
        } else {
          goto handle_unusual;
        }
        if (input->ExpectTag(72)) goto parse_lda;
        break;
      }

      // required int32 lda = 9;
      case 9: {
        if (tag == 72) {
         parse_lda:
          DO_((::google::protobuf::internal::WireFormatLite::ReadPrimitive<
                   ::google::protobuf::int32, ::google::protobuf::internal::WireFormatLite::TYPE_INT32>(
                 input, &lda_)));
          set_has_lda();
        } else {
          goto handle_unusual;
        }
        if (input->ExpectTag(80)) goto parse_B;
        break;
      }

      // required int64 B = 10;
      case 10: {
        if (tag == 80) {
         parse_B:
          DO_((::google::protobuf::internal::WireFormatLite::ReadPrimitive<
                   ::google::protobuf::int64, ::google::protobuf::internal::WireFormatLite::TYPE_INT64>(
                 input, &b_)));
          set_has_b();
        } else {
          goto handle_unusual;
        }
        if (input->ExpectTag(88)) goto parse_ldb;
        break;
      }

      // required int32 ldb = 11;
      case 11: {
        if (tag == 88) {
         parse_ldb:
          DO_((::google::protobuf::internal::WireFormatLite::ReadPrimitive<
                   ::google::protobuf::int32, ::google::protobuf::internal::WireFormatLite::TYPE_INT32>(
                 input, &ldb_)));
          set_has_ldb();
        } else {
          goto handle_unusual;
        }
        if (input->ExpectTag(97)) goto parse_beta;
        break;
      }

      // required double beta = 12;
      case 12: {
        if (tag == 97) {
         parse_beta:
          DO_((::google::protobuf::internal::WireFormatLite::ReadPrimitive<
                   double, ::google::protobuf::internal::WireFormatLite::TYPE_DOUBLE>(
                 input, &beta_)));
          set_has_beta();
        } else {
          goto handle_unusual;
        }
        if (input->ExpectTag(104)) goto parse_C;
        break;
      }

      // required int64 C = 13;
      case 13: {
        if (tag == 104) {
         parse_C:
          DO_((::google::protobuf::internal::WireFormatLite::ReadPrimitive<
                   ::google::protobuf::int64, ::google::protobuf::internal::WireFormatLite::TYPE_INT64>(
                 input, &c_)));
          set_has_c();
        } else {
          goto handle_unusual;
        }
        if (input->ExpectTag(112)) goto parse_ldc;
        break;
      }

      // required int32 ldc = 14;
      case 14: {
        if (tag == 112) {
         parse_ldc:
          DO_((::google::protobuf::internal::WireFormatLite::ReadPrimitive<
                   ::google::protobuf::int32, ::google::protobuf::internal::WireFormatLite::TYPE_INT32>(
                 input, &ldc_)));
          set_has_ldc();
        } else {
          goto handle_unusual;
        }
        if (input->ExpectAtEnd()) goto success;
        break;
      }

      default: {
      handle_unusual:
        if (tag == 0 ||
            ::google::protobuf::internal::WireFormatLite::GetTagWireType(tag) ==
            ::google::protobuf::internal::WireFormatLite::WIRETYPE_END_GROUP) {
          goto success;
        }
        DO_(::google::protobuf::internal::WireFormat::SkipField(
              input, tag, mutable_unknown_fields()));
        break;
      }
    }
  }
success:
  // @@protoc_insertion_point(parse_success:clblasargs.DGEMMMessage)
  return true;
failure:
  // @@protoc_insertion_point(parse_failure:clblasargs.DGEMMMessage)
  return false;
#undef DO_
}

void DGEMMMessage::SerializeWithCachedSizes(
    ::google::protobuf::io::CodedOutputStream* output) const {
  // @@protoc_insertion_point(serialize_start:clblasargs.DGEMMMessage)
  // required int32 order = 1;
  if (has_order()) {
    ::google::protobuf::internal::WireFormatLite::WriteInt32(1, this->order(), output);
  }

  // required int32 transA = 2;
  if (has_transa()) {
    ::google::protobuf::internal::WireFormatLite::WriteInt32(2, this->transa(), output);
  }

  // required int32 transB = 3;
  if (has_transb()) {
    ::google::protobuf::internal::WireFormatLite::WriteInt32(3, this->transb(), output);
  }

  // required int32 M = 4;
  if (has_m()) {
    ::google::protobuf::internal::WireFormatLite::WriteInt32(4, this->m(), output);
  }

  // required int32 N = 5;
  if (has_n()) {
    ::google::protobuf::internal::WireFormatLite::WriteInt32(5, this->n(), output);
  }

  // required int32 K = 6;
  if (has_k()) {
    ::google::protobuf::internal::WireFormatLite::WriteInt32(6, this->k(), output);
  }

  // required double alpha = 7;
  if (has_alpha()) {
    ::google::protobuf::internal::WireFormatLite::WriteDouble(7, this->alpha(), output);
  }

  // required int64 A = 8;
  if (has_a()) {
    ::google::protobuf::internal::WireFormatLite::WriteInt64(8, this->a(), output);
  }

  // required int32 lda = 9;
  if (has_lda()) {
    ::google::protobuf::internal::WireFormatLite::WriteInt32(9, this->lda(), output);
  }

  // required int64 B = 10;
  if (has_b()) {
    ::google::protobuf::internal::WireFormatLite::WriteInt64(10, this->b(), output);
  }

  // required int32 ldb = 11;
  if (has_ldb()) {
    ::google::protobuf::internal::WireFormatLite::WriteInt32(11, this->ldb(), output);
  }

  // required double beta = 12;
  if (has_beta()) {
    ::google::protobuf::internal::WireFormatLite::WriteDouble(12, this->beta(), output);
  }

  // required int64 C = 13;
  if (has_c()) {
    ::google::protobuf::internal::WireFormatLite::WriteInt64(13, this->c(), output);
  }

  // required int32 ldc = 14;
  if (has_ldc()) {
    ::google::protobuf::internal::WireFormatLite::WriteInt32(14, this->ldc(), output);
  }

  if (_internal_metadata_.have_unknown_fields()) {
    ::google::protobuf::internal::WireFormat::SerializeUnknownFields(
        unknown_fields(), output);
  }
  // @@protoc_insertion_point(serialize_end:clblasargs.DGEMMMessage)
}

::google::protobuf::uint8* DGEMMMessage::SerializeWithCachedSizesToArray(
    ::google::protobuf::uint8* target) const {
  // @@protoc_insertion_point(serialize_to_array_start:clblasargs.DGEMMMessage)
  // required int32 order = 1;
  if (has_order()) {
    target = ::google::protobuf::internal::WireFormatLite::WriteInt32ToArray(1, this->order(), target);
  }

  // required int32 transA = 2;
  if (has_transa()) {
    target = ::google::protobuf::internal::WireFormatLite::WriteInt32ToArray(2, this->transa(), target);
  }

  // required int32 transB = 3;
  if (has_transb()) {
    target = ::google::protobuf::internal::WireFormatLite::WriteInt32ToArray(3, this->transb(), target);
  }

  // required int32 M = 4;
  if (has_m()) {
    target = ::google::protobuf::internal::WireFormatLite::WriteInt32ToArray(4, this->m(), target);
  }

  // required int32 N = 5;
  if (has_n()) {
    target = ::google::protobuf::internal::WireFormatLite::WriteInt32ToArray(5, this->n(), target);
  }

  // required int32 K = 6;
  if (has_k()) {
    target = ::google::protobuf::internal::WireFormatLite::WriteInt32ToArray(6, this->k(), target);
  }

  // required double alpha = 7;
  if (has_alpha()) {
    target = ::google::protobuf::internal::WireFormatLite::WriteDoubleToArray(7, this->alpha(), target);
  }

  // required int64 A = 8;
  if (has_a()) {
    target = ::google::protobuf::internal::WireFormatLite::WriteInt64ToArray(8, this->a(), target);
  }

  // required int32 lda = 9;
  if (has_lda()) {
    target = ::google::protobuf::internal::WireFormatLite::WriteInt32ToArray(9, this->lda(), target);
  }

  // required int64 B = 10;
  if (has_b()) {
    target = ::google::protobuf::internal::WireFormatLite::WriteInt64ToArray(10, this->b(), target);
  }

  // required int32 ldb = 11;
  if (has_ldb()) {
    target = ::google::protobuf::internal::WireFormatLite::WriteInt32ToArray(11, this->ldb(), target);
  }

  // required double beta = 12;
  if (has_beta()) {
    target = ::google::protobuf::internal::WireFormatLite::WriteDoubleToArray(12, this->beta(), target);
  }

  // required int64 C = 13;
  if (has_c()) {
    target = ::google::protobuf::internal::WireFormatLite::WriteInt64ToArray(13, this->c(), target);
  }

  // required int32 ldc = 14;
  if (has_ldc()) {
    target = ::google::protobuf::internal::WireFormatLite::WriteInt32ToArray(14, this->ldc(), target);
  }

  if (_internal_metadata_.have_unknown_fields()) {
    target = ::google::protobuf::internal::WireFormat::SerializeUnknownFieldsToArray(
        unknown_fields(), target);
  }
  // @@protoc_insertion_point(serialize_to_array_end:clblasargs.DGEMMMessage)
  return target;
}

int DGEMMMessage::RequiredFieldsByteSizeFallback() const {
  int total_size = 0;

  if (has_order()) {
    // required int32 order = 1;
    total_size += 1 +
      ::google::protobuf::internal::WireFormatLite::Int32Size(
        this->order());
  }

  if (has_transa()) {
    // required int32 transA = 2;
    total_size += 1 +
      ::google::protobuf::internal::WireFormatLite::Int32Size(
        this->transa());
  }

  if (has_transb()) {
    // required int32 transB = 3;
    total_size += 1 +
      ::google::protobuf::internal::WireFormatLite::Int32Size(
        this->transb());
  }

  if (has_m()) {
    // required int32 M = 4;
    total_size += 1 +
      ::google::protobuf::internal::WireFormatLite::Int32Size(
        this->m());
  }

  if (has_n()) {
    // required int32 N = 5;
    total_size += 1 +
      ::google::protobuf::internal::WireFormatLite::Int32Size(
        this->n());
  }

  if (has_k()) {
    // required int32 K = 6;
    total_size += 1 +
      ::google::protobuf::internal::WireFormatLite::Int32Size(
        this->k());
  }

  if (has_alpha()) {
    // required double alpha = 7;
    total_size += 1 + 8;
  }

  if (has_a()) {
    // required int64 A = 8;
    total_size += 1 +
      ::google::protobuf::internal::WireFormatLite::Int64Size(
        this->a());
  }

  if (has_lda()) {
    // required int32 lda = 9;
    total_size += 1 +
      ::google::protobuf::internal::WireFormatLite::Int32Size(
        this->lda());
  }

  if (has_b()) {
    // required int64 B = 10;
    total_size += 1 +
      ::google::protobuf::internal::WireFormatLite::Int64Size(
        this->b());
  }

  if (has_ldb()) {
    // required int32 ldb = 11;
    total_size += 1 +
      ::google::protobuf::internal::WireFormatLite::Int32Size(
        this->ldb());
  }

  if (has_beta()) {
    // required double beta = 12;
    total_size += 1 + 8;
  }

  if (has_c()) {
    // required int64 C = 13;
    total_size += 1 +
      ::google::protobuf::internal::WireFormatLite::Int64Size(
        this->c());
  }

  if (has_ldc()) {
    // required int32 ldc = 14;
    total_size += 1 +
      ::google::protobuf::internal::WireFormatLite::Int32Size(
        this->ldc());
  }

  return total_size;
}
int DGEMMMessage::ByteSize() const {
  int total_size = 0;

  if (((_has_bits_[0] & 0x00003fff) ^ 0x00003fff) == 0) {  // All required fields are present.
    // required int32 order = 1;
    total_size += 1 +
      ::google::protobuf::internal::WireFormatLite::Int32Size(
        this->order());

    // required int32 transA = 2;
    total_size += 1 +
      ::google::protobuf::internal::WireFormatLite::Int32Size(
        this->transa());

    // required int32 transB = 3;
    total_size += 1 +
      ::google::protobuf::internal::WireFormatLite::Int32Size(
        this->transb());

    // required int32 M = 4;
    total_size += 1 +
      ::google::protobuf::internal::WireFormatLite::Int32Size(
        this->m());

    // required int32 N = 5;
    total_size += 1 +
      ::google::protobuf::internal::WireFormatLite::Int32Size(
        this->n());

    // required int32 K = 6;
    total_size += 1 +
      ::google::protobuf::internal::WireFormatLite::Int32Size(
        this->k());

    // required double alpha = 7;
    total_size += 1 + 8;

    // required int64 A = 8;
    total_size += 1 +
      ::google::protobuf::internal::WireFormatLite::Int64Size(
        this->a());

    // required int32 lda = 9;
    total_size += 1 +
      ::google::protobuf::internal::WireFormatLite::Int32Size(
        this->lda());

    // required int64 B = 10;
    total_size += 1 +
      ::google::protobuf::internal::WireFormatLite::Int64Size(
        this->b());

    // required int32 ldb = 11;
    total_size += 1 +
      ::google::protobuf::internal::WireFormatLite::Int32Size(
        this->ldb());

    // required double beta = 12;
    total_size += 1 + 8;

    // required int64 C = 13;
    total_size += 1 +
      ::google::protobuf::internal::WireFormatLite::Int64Size(
        this->c());

    // required int32 ldc = 14;
    total_size += 1 +
      ::google::protobuf::internal::WireFormatLite::Int32Size(
        this->ldc());

  } else {
    total_size += RequiredFieldsByteSizeFallback();
  }
  if (_internal_metadata_.have_unknown_fields()) {
    total_size +=
      ::google::protobuf::internal::WireFormat::ComputeUnknownFieldsSize(
        unknown_fields());
  }
  GOOGLE_SAFE_CONCURRENT_WRITES_BEGIN();
  _cached_size_ = total_size;
  GOOGLE_SAFE_CONCURRENT_WRITES_END();
  return total_size;
}

void DGEMMMessage::MergeFrom(const ::google::protobuf::Message& from) {
  if (GOOGLE_PREDICT_FALSE(&from == this)) MergeFromFail(__LINE__);
  const DGEMMMessage* source =
    ::google::protobuf::internal::dynamic_cast_if_available<const DGEMMMessage*>(
      &from);
  if (source == NULL) {
    ::google::protobuf::internal::ReflectionOps::Merge(from, this);
  } else {
    MergeFrom(*source);
  }
}

void DGEMMMessage::MergeFrom(const DGEMMMessage& from) {
  if (GOOGLE_PREDICT_FALSE(&from == this)) MergeFromFail(__LINE__);
  if (from._has_bits_[0 / 32] & (0xffu << (0 % 32))) {
    if (from.has_order()) {
      set_order(from.order());
    }
    if (from.has_transa()) {
      set_transa(from.transa());
    }
    if (from.has_transb()) {
      set_transb(from.transb());
    }
    if (from.has_m()) {
      set_m(from.m());
    }
    if (from.has_n()) {
      set_n(from.n());
    }
    if (from.has_k()) {
      set_k(from.k());
    }
    if (from.has_alpha()) {
      set_alpha(from.alpha());
    }
    if (from.has_a()) {
      set_a(from.a());
    }
  }
  if (from._has_bits_[8 / 32] & (0xffu << (8 % 32))) {
    if (from.has_lda()) {
      set_lda(from.lda());
    }
    if (from.has_b()) {
      set_b(from.b());
    }
    if (from.has_ldb()) {
      set_ldb(from.ldb());
    }
    if (from.has_beta()) {
      set_beta(from.beta());
    }
    if (from.has_c()) {
      set_c(from.c());
    }
    if (from.has_ldc()) {
      set_ldc(from.ldc());
    }
  }
  if (from._internal_metadata_.have_unknown_fields()) {
    mutable_unknown_fields()->MergeFrom(from.unknown_fields());
  }
}

void DGEMMMessage::CopyFrom(const ::google::protobuf::Message& from) {
  if (&from == this) return;
  Clear();
  MergeFrom(from);
}

void DGEMMMessage::CopyFrom(const DGEMMMessage& from) {
  if (&from == this) return;
  Clear();
  MergeFrom(from);
}

bool DGEMMMessage::IsInitialized() const {
  if ((_has_bits_[0] & 0x00003fff) != 0x00003fff) return false;

  return true;
}

void DGEMMMessage::Swap(DGEMMMessage* other) {
  if (other == this) return;
  InternalSwap(other);
}
void DGEMMMessage::InternalSwap(DGEMMMessage* other) {
  std::swap(order_, other->order_);
  std::swap(transa_, other->transa_);
  std::swap(transb_, other->transb_);
  std::swap(m_, other->m_);
  std::swap(n_, other->n_);
  std::swap(k_, other->k_);
  std::swap(alpha_, other->alpha_);
  std::swap(a_, other->a_);
  std::swap(lda_, other->lda_);
  std::swap(b_, other->b_);
  std::swap(ldb_, other->ldb_);
  std::swap(beta_, other->beta_);
  std::swap(c_, other->c_);
  std::swap(ldc_, other->ldc_);
  std::swap(_has_bits_[0], other->_has_bits_[0]);
  _internal_metadata_.Swap(&other->_internal_metadata_);
  std::swap(_cached_size_, other->_cached_size_);
}

::google::protobuf::Metadata DGEMMMessage::GetMetadata() const {
  protobuf_AssignDescriptorsOnce();
  ::google::protobuf::Metadata metadata;
  metadata.descriptor = DGEMMMessage_descriptor_;
  metadata.reflection = DGEMMMessage_reflection_;
  return metadata;
}


// @@protoc_insertion_point(namespace_scope)

}  // namespace clblasargs

// @@protoc_insertion_point(global_scope)