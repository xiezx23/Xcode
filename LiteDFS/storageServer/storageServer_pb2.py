# -*- coding: utf-8 -*-
# Generated by the protocol buffer compiler.  DO NOT EDIT!
# source: storageServer.proto
"""Generated protocol buffer code."""
from google.protobuf.internal import builder as _builder
from google.protobuf import descriptor as _descriptor
from google.protobuf import descriptor_pool as _descriptor_pool
from google.protobuf import symbol_database as _symbol_database
# @@protoc_insertion_point(imports)

_sym_db = _symbol_database.Default()




DESCRIPTOR = _descriptor_pool.Default().AddSerializedFile(b'\n\x13storageServer.proto\"+\n\x0bupload_file\x12\x0c\n\x04path\x18\x01 \x01(\t\x12\x0e\n\x06\x62uffer\x18\x02 \x01(\x0c\"\x19\n\tfile_path\x12\x0c\n\x04path\x18\x01 \x01(\t\"\x15\n\x05reply\x12\x0c\n\x04\x64one\x18\x01 \x01(\x08\"\x1c\n\nfileStream\x12\x0e\n\x06\x62uffer\x18\x01 \x01(\x0c\"\x18\n\x08\x66ileList\x12\x0c\n\x04list\x18\x01 \x01(\t2\x84\x02\n\rstorageServer\x12%\n\tsynUpload\x12\x0c.upload_file\x1a\x06.reply\"\x00(\x01\x12\"\n\x06upload\x12\x0c.upload_file\x1a\x06.reply\"\x00(\x01\x12\'\n\x08\x64ownload\x12\n.file_path\x1a\x0b.fileStream\"\x00\x30\x01\x12\x1d\n\x02ls\x12\n.file_path\x1a\t.fileList\"\x00\x12\x1d\n\x05mkdir\x12\n.file_path\x1a\x06.reply\"\x00\x12!\n\tsynDelete\x12\n.file_path\x1a\x06.reply\"\x00\x12\x1e\n\x06\x64\x65lete\x12\n.file_path\x1a\x06.reply\"\x00\x62\x06proto3')

_builder.BuildMessageAndEnumDescriptors(DESCRIPTOR, globals())
_builder.BuildTopDescriptorsAndMessages(DESCRIPTOR, 'storageServer_pb2', globals())
if _descriptor._USE_C_DESCRIPTORS == False:

  DESCRIPTOR._options = None
  _UPLOAD_FILE._serialized_start=23
  _UPLOAD_FILE._serialized_end=66
  _FILE_PATH._serialized_start=68
  _FILE_PATH._serialized_end=93
  _REPLY._serialized_start=95
  _REPLY._serialized_end=116
  _FILESTREAM._serialized_start=118
  _FILESTREAM._serialized_end=146
  _FILELIST._serialized_start=148
  _FILELIST._serialized_end=172
  _STORAGESERVER._serialized_start=175
  _STORAGESERVER._serialized_end=435
# @@protoc_insertion_point(module_scope)