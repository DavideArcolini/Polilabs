// Generated by the protocol buffer compiler.  DO NOT EDIT!
// source: conversion.proto

package conversion;

public final class ConversionProto {
  private ConversionProto() {}
  public static void registerAllExtensions(
      com.google.protobuf.ExtensionRegistryLite registry) {
  }

  public static void registerAllExtensions(
      com.google.protobuf.ExtensionRegistry registry) {
    registerAllExtensions(
        (com.google.protobuf.ExtensionRegistryLite) registry);
  }
  static final com.google.protobuf.Descriptors.Descriptor
    internal_static_conversion_ConversionRequest_descriptor;
  static final 
    com.google.protobuf.GeneratedMessageV3.FieldAccessorTable
      internal_static_conversion_ConversionRequest_fieldAccessorTable;
  static final com.google.protobuf.Descriptors.Descriptor
    internal_static_conversion_MetadataRequest_descriptor;
  static final 
    com.google.protobuf.GeneratedMessageV3.FieldAccessorTable
      internal_static_conversion_MetadataRequest_fieldAccessorTable;
  static final com.google.protobuf.Descriptors.Descriptor
    internal_static_conversion_ConversionReply_descriptor;
  static final 
    com.google.protobuf.GeneratedMessageV3.FieldAccessorTable
      internal_static_conversion_ConversionReply_fieldAccessorTable;
  static final com.google.protobuf.Descriptors.Descriptor
    internal_static_conversion_MetadataReply_descriptor;
  static final 
    com.google.protobuf.GeneratedMessageV3.FieldAccessorTable
      internal_static_conversion_MetadataReply_fieldAccessorTable;

  public static com.google.protobuf.Descriptors.FileDescriptor
      getDescriptor() {
    return descriptor;
  }
  private static  com.google.protobuf.Descriptors.FileDescriptor
      descriptor;
  static {
    java.lang.String[] descriptorData = {
      "\n\020conversion.proto\022\nconversion\"a\n\021Conver" +
      "sionRequest\022+\n\004meta\030\001 \001(\0132\033.conversion.M" +
      "etadataRequestH\000\022\016\n\004file\030\002 \001(\014H\000B\017\n\rrequ" +
      "est_oneof\"E\n\017MetadataRequest\022\030\n\020file_typ" +
      "e_origin\030\001 \001(\t\022\030\n\020file_type_target\030\002 \001(\t" +
      "\"]\n\017ConversionReply\022)\n\004meta\030\001 \001(\0132\031.conv" +
      "ersion.MetadataReplyH\000\022\016\n\004file\030\002 \001(\014H\000B\017" +
      "\n\rrequest_oneof\"/\n\rMetadataReply\022\017\n\007succ" +
      "ess\030\001 \001(\010\022\r\n\005error\030\002 \001(\t2\\\n\tConverter\022O\n" +
      "\013fileConvert\022\035.conversion.ConversionRequ" +
      "est\032\033.conversion.ConversionReply\"\000(\0010\001B$" +
      "\n\nconversionB\017ConversionProtoP\001\242\002\002CPb\006pr" +
      "oto3"
    };
    descriptor = com.google.protobuf.Descriptors.FileDescriptor
      .internalBuildGeneratedFileFrom(descriptorData,
        new com.google.protobuf.Descriptors.FileDescriptor[] {
        });
    internal_static_conversion_ConversionRequest_descriptor =
      getDescriptor().getMessageTypes().get(0);
    internal_static_conversion_ConversionRequest_fieldAccessorTable = new
      com.google.protobuf.GeneratedMessageV3.FieldAccessorTable(
        internal_static_conversion_ConversionRequest_descriptor,
        new java.lang.String[] { "Meta", "File", "RequestOneof", });
    internal_static_conversion_MetadataRequest_descriptor =
      getDescriptor().getMessageTypes().get(1);
    internal_static_conversion_MetadataRequest_fieldAccessorTable = new
      com.google.protobuf.GeneratedMessageV3.FieldAccessorTable(
        internal_static_conversion_MetadataRequest_descriptor,
        new java.lang.String[] { "FileTypeOrigin", "FileTypeTarget", });
    internal_static_conversion_ConversionReply_descriptor =
      getDescriptor().getMessageTypes().get(2);
    internal_static_conversion_ConversionReply_fieldAccessorTable = new
      com.google.protobuf.GeneratedMessageV3.FieldAccessorTable(
        internal_static_conversion_ConversionReply_descriptor,
        new java.lang.String[] { "Meta", "File", "RequestOneof", });
    internal_static_conversion_MetadataReply_descriptor =
      getDescriptor().getMessageTypes().get(3);
    internal_static_conversion_MetadataReply_fieldAccessorTable = new
      com.google.protobuf.GeneratedMessageV3.FieldAccessorTable(
        internal_static_conversion_MetadataReply_descriptor,
        new java.lang.String[] { "Success", "Error", });
  }

  // @@protoc_insertion_point(outer_class_scope)
}