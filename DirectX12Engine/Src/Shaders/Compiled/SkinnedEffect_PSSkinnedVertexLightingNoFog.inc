#if 0
;
; Input signature:
;
; Name                 Index   Mask Register SysValue  Format   Used
; -------------------- ----- ------ -------- -------- ------- ------
; COLOR                    0   xyzw        0     NONE   float   xyzw
; COLOR                    1   xyzw        1     NONE   float   xyz 
; TEXCOORD                 0   xy          2     NONE   float   xy  
;
;
; Output signature:
;
; Name                 Index   Mask Register SysValue  Format   Used
; -------------------- ----- ------ -------- -------- ------- ------
; SV_Target                0   xyzw        0   TARGET   float   xyzw
;
; shader debug name: Compiled\SkinnedEffect_PSSkinnedVertexLightingNoFog.pdb
; shader hash: 050f8911b694173bc2c1f818f0c2a484
;
; Pipeline Runtime Information: 
;
; Pixel Shader
; DepthOutput=0
; SampleFrequency=0
;
;
; Input signature:
;
; Name                 Index             InterpMode DynIdx
; -------------------- ----- ---------------------- ------
; COLOR                    0                 linear       
; COLOR                    1                 linear       
; TEXCOORD                 0                 linear       
;
; Output signature:
;
; Name                 Index             InterpMode DynIdx
; -------------------- ----- ---------------------- ------
; SV_Target                0                              
;
; Buffer Definitions:
;
;
; Resource Bindings:
;
; Name                                 Type  Format         Dim      ID      HLSL Bind  Count
; ------------------------------ ---------- ------- ----------- ------- -------------- ------
;                                   sampler      NA          NA      S0             s0     1
;                                   texture     f32          2d      T0             t0     1
;
;
; ViewId state:
;
; Number of inputs: 10, outputs: 4
; Outputs dependent on ViewId: {  }
; Inputs contributing to computation of Outputs:
;   output 0 depends on inputs: { 0, 3, 4, 8, 9 }
;   output 1 depends on inputs: { 1, 3, 5, 8, 9 }
;   output 2 depends on inputs: { 2, 3, 6, 8, 9 }
;   output 3 depends on inputs: { 3, 8, 9 }
;
target datalayout = "e-m:e-p:32:32-i1:32-i8:32-i16:32-i32:32-i64:64-f16:32-f32:32-f64:64-n8:16:32:64"
target triple = "dxil-ms-dx"

%dx.types.Handle = type { i8* }
%dx.types.ResRet.f32 = type { float, float, float, float, i32 }
%"class.Texture2D<vector<float, 4> >" = type { <4 x float>, %"class.Texture2D<vector<float, 4> >::mips_type" }
%"class.Texture2D<vector<float, 4> >::mips_type" = type { i32 }
%struct.SamplerState = type { i32 }

define void @PSSkinnedVertexLightingNoFog() {
  %1 = call %dx.types.Handle @dx.op.createHandle(i32 57, i8 0, i32 0, i32 0, i1 false)  ; CreateHandle(resourceClass,rangeId,index,nonUniformIndex)
  %2 = call %dx.types.Handle @dx.op.createHandle(i32 57, i8 3, i32 0, i32 0, i1 false)  ; CreateHandle(resourceClass,rangeId,index,nonUniformIndex)
  %3 = call float @dx.op.loadInput.f32(i32 4, i32 2, i32 0, i8 0, i32 undef)  ; LoadInput(inputSigId,rowIndex,colIndex,gsVertexAxis)
  %4 = call float @dx.op.loadInput.f32(i32 4, i32 2, i32 0, i8 1, i32 undef)  ; LoadInput(inputSigId,rowIndex,colIndex,gsVertexAxis)
  %5 = call float @dx.op.loadInput.f32(i32 4, i32 1, i32 0, i8 0, i32 undef)  ; LoadInput(inputSigId,rowIndex,colIndex,gsVertexAxis)
  %6 = call float @dx.op.loadInput.f32(i32 4, i32 1, i32 0, i8 1, i32 undef)  ; LoadInput(inputSigId,rowIndex,colIndex,gsVertexAxis)
  %7 = call float @dx.op.loadInput.f32(i32 4, i32 1, i32 0, i8 2, i32 undef)  ; LoadInput(inputSigId,rowIndex,colIndex,gsVertexAxis)
  %8 = call float @dx.op.loadInput.f32(i32 4, i32 0, i32 0, i8 0, i32 undef)  ; LoadInput(inputSigId,rowIndex,colIndex,gsVertexAxis)
  %9 = call float @dx.op.loadInput.f32(i32 4, i32 0, i32 0, i8 1, i32 undef)  ; LoadInput(inputSigId,rowIndex,colIndex,gsVertexAxis)
  %10 = call float @dx.op.loadInput.f32(i32 4, i32 0, i32 0, i8 2, i32 undef)  ; LoadInput(inputSigId,rowIndex,colIndex,gsVertexAxis)
  %11 = call float @dx.op.loadInput.f32(i32 4, i32 0, i32 0, i8 3, i32 undef)  ; LoadInput(inputSigId,rowIndex,colIndex,gsVertexAxis)
  %12 = call %dx.types.ResRet.f32 @dx.op.sample.f32(i32 60, %dx.types.Handle %1, %dx.types.Handle %2, float %3, float %4, float undef, float undef, i32 0, i32 0, i32 undef, float undef)  ; Sample(srv,sampler,coord0,coord1,coord2,coord3,offset0,offset1,offset2,clamp)
  %13 = extractvalue %dx.types.ResRet.f32 %12, 0
  %14 = extractvalue %dx.types.ResRet.f32 %12, 1
  %15 = extractvalue %dx.types.ResRet.f32 %12, 2
  %16 = extractvalue %dx.types.ResRet.f32 %12, 3
  %17 = fmul fast float %13, %8
  %18 = fmul fast float %14, %9
  %19 = fmul fast float %15, %10
  %20 = fmul fast float %16, %11
  %21 = fmul fast float %20, %5
  %22 = fmul fast float %20, %6
  %23 = fmul fast float %20, %7
  %24 = fadd fast float %21, %17
  %25 = fadd fast float %22, %18
  %26 = fadd fast float %23, %19
  call void @dx.op.storeOutput.f32(i32 5, i32 0, i32 0, i8 0, float %24)  ; StoreOutput(outputSigId,rowIndex,colIndex,value)
  call void @dx.op.storeOutput.f32(i32 5, i32 0, i32 0, i8 1, float %25)  ; StoreOutput(outputSigId,rowIndex,colIndex,value)
  call void @dx.op.storeOutput.f32(i32 5, i32 0, i32 0, i8 2, float %26)  ; StoreOutput(outputSigId,rowIndex,colIndex,value)
  call void @dx.op.storeOutput.f32(i32 5, i32 0, i32 0, i8 3, float %20)  ; StoreOutput(outputSigId,rowIndex,colIndex,value)
  ret void
}

; Function Attrs: nounwind readnone
declare float @dx.op.loadInput.f32(i32, i32, i32, i8, i32) #0

; Function Attrs: nounwind
declare void @dx.op.storeOutput.f32(i32, i32, i32, i8, float) #1

; Function Attrs: nounwind readonly
declare %dx.types.ResRet.f32 @dx.op.sample.f32(i32, %dx.types.Handle, %dx.types.Handle, float, float, float, float, i32, i32, i32, float) #2

; Function Attrs: nounwind readonly
declare %dx.types.Handle @dx.op.createHandle(i32, i8, i32, i32, i1) #2

attributes #0 = { nounwind readnone }
attributes #1 = { nounwind }
attributes #2 = { nounwind readonly }

!llvm.ident = !{!0}
!dx.version = !{!1}
!dx.valver = !{!2}
!dx.shaderModel = !{!3}
!dx.resources = !{!4}
!dx.viewIdState = !{!10}
!dx.entryPoints = !{!11}

!0 = !{!"clang version 3.7 (tags/RELEASE_370/final)"}
!1 = !{i32 1, i32 0}
!2 = !{i32 1, i32 6}
!3 = !{!"ps", i32 6, i32 0}
!4 = !{!5, null, null, !8}
!5 = !{!6}
!6 = !{i32 0, %"class.Texture2D<vector<float, 4> >"* undef, !"", i32 0, i32 0, i32 1, i32 2, i32 0, !7}
!7 = !{i32 0, i32 9}
!8 = !{!9}
!9 = !{i32 0, %struct.SamplerState* undef, !"", i32 0, i32 0, i32 1, i32 0, null}
!10 = !{[12 x i32] [i32 10, i32 4, i32 1, i32 2, i32 4, i32 15, i32 1, i32 2, i32 4, i32 0, i32 15, i32 15]}
!11 = !{void ()* @PSSkinnedVertexLightingNoFog, !"PSSkinnedVertexLightingNoFog", !12, !4, null}
!12 = !{!13, !22, null}
!13 = !{!14, !17, !20}
!14 = !{i32 0, !"COLOR", i8 9, i8 0, !15, i8 2, i32 1, i8 4, i32 0, i8 0, !16}
!15 = !{i32 0}
!16 = !{i32 3, i32 15}
!17 = !{i32 1, !"COLOR", i8 9, i8 0, !18, i8 2, i32 1, i8 4, i32 1, i8 0, !19}
!18 = !{i32 1}
!19 = !{i32 3, i32 7}
!20 = !{i32 2, !"TEXCOORD", i8 9, i8 0, !15, i8 2, i32 1, i8 2, i32 2, i8 0, !21}
!21 = !{i32 3, i32 3}
!22 = !{!23}
!23 = !{i32 0, !"SV_Target", i8 9, i8 16, !15, i8 0, i32 1, i8 4, i32 0, i8 0, !16}

#endif

const unsigned char SkinnedEffect_PSSkinnedVertexLightingNoFog[] = {
  0x44, 0x58, 0x42, 0x43, 0xee, 0xf2, 0xc1, 0xe7, 0x75, 0x65, 0x44, 0xfb,
  0x4b, 0x59, 0x4c, 0xbf, 0xb7, 0x61, 0x02, 0x18, 0x01, 0x00, 0x00, 0x00,
  0x6b, 0x0a, 0x00, 0x00, 0x08, 0x00, 0x00, 0x00, 0x40, 0x00, 0x00, 0x00,
  0x50, 0x00, 0x00, 0x00, 0xd5, 0x00, 0x00, 0x00, 0x0f, 0x01, 0x00, 0x00,
  0x1f, 0x02, 0x00, 0x00, 0xaf, 0x02, 0x00, 0x00, 0xf3, 0x02, 0x00, 0x00,
  0x0f, 0x03, 0x00, 0x00, 0x53, 0x46, 0x49, 0x30, 0x08, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x49, 0x53, 0x47, 0x31,
  0x7d, 0x00, 0x00, 0x00, 0x03, 0x00, 0x00, 0x00, 0x08, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x68, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x03, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x0f, 0x0f, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x6e, 0x00, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x03, 0x00, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00, 0x0f, 0x07, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x74, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x03, 0x00, 0x00, 0x00,
  0x02, 0x00, 0x00, 0x00, 0x03, 0x03, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x43, 0x4f, 0x4c, 0x4f, 0x52, 0x00, 0x43, 0x4f, 0x4c, 0x4f, 0x52, 0x00,
  0x54, 0x45, 0x58, 0x43, 0x4f, 0x4f, 0x52, 0x44, 0x00, 0x4f, 0x53, 0x47,
  0x31, 0x32, 0x00, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00, 0x08, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x28, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x40, 0x00, 0x00, 0x00, 0x03, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x0f, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x53, 0x56, 0x5f,
  0x54, 0x61, 0x72, 0x67, 0x65, 0x74, 0x00, 0x50, 0x53, 0x56, 0x30, 0x08,
  0x01, 0x00, 0x00, 0x30, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0xff, 0xff, 0xff, 0xff, 0x00, 0x00, 0x00, 0x00, 0x03,
  0x01, 0x00, 0x03, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x02, 0x00, 0x00, 0x00, 0x18,
  0x00, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x0e, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x03, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x02, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x18, 0x00, 0x00, 0x00, 0x00, 0x43, 0x4f, 0x4c, 0x4f,
  0x52, 0x00, 0x43, 0x4f, 0x4c, 0x4f, 0x52, 0x00, 0x54, 0x45, 0x58, 0x43,
  0x4f, 0x4f, 0x52, 0x44, 0x00, 0x00, 0x00, 0x02, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00, 0x10, 0x00, 0x00, 0x00, 0x01,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x00, 0x44, 0x00, 0x03,
  0x02, 0x00, 0x00, 0x07, 0x00, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00, 0x01,
  0x01, 0x44, 0x00, 0x03, 0x02, 0x00, 0x00, 0x0d, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x01, 0x02, 0x42, 0x00, 0x03, 0x02, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x00, 0x44, 0x10, 0x03,
  0x00, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00, 0x02, 0x00, 0x00, 0x00, 0x04,
  0x00, 0x00, 0x00, 0x0f, 0x00, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00, 0x02,
  0x00, 0x00, 0x00, 0x04, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x0f,
  0x00, 0x00, 0x00, 0x0f, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x52, 0x54, 0x53, 0x30, 0x88, 0x00, 0x00, 0x00, 0x02,
  0x00, 0x00, 0x00, 0x03, 0x00, 0x00, 0x00, 0x18, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x88, 0x00, 0x00, 0x00, 0x1d, 0x00, 0x00, 0x00, 0x02,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x3c, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x05, 0x00, 0x00, 0x00, 0x48, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x05, 0x00, 0x00, 0x00, 0x68, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01,
  0x00, 0x00, 0x00, 0x50, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0xff, 0xff, 0xff, 0xff, 0x01, 0x00, 0x00, 0x00, 0x70,
  0x00, 0x00, 0x00, 0x03, 0x00, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xff,
  0xff, 0xff, 0xff, 0x49, 0x4c, 0x44, 0x4e, 0x3c, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x37, 0x00, 0x43, 0x6f, 0x6d, 0x70, 0x69, 0x6c, 0x65, 0x64, 0x5c,
  0x53, 0x6b, 0x69, 0x6e, 0x6e, 0x65, 0x64, 0x45, 0x66, 0x66, 0x65, 0x63,
  0x74, 0x5f, 0x50, 0x53, 0x53, 0x6b, 0x69, 0x6e, 0x6e, 0x65, 0x64, 0x56,
  0x65, 0x72, 0x74, 0x65, 0x78, 0x4c, 0x69, 0x67, 0x68, 0x74, 0x69, 0x6e,
  0x67, 0x4e, 0x6f, 0x46, 0x6f, 0x67, 0x2e, 0x70, 0x64, 0x62, 0x00, 0x48,
  0x41, 0x53, 0x48, 0x14, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x05,
  0x0f, 0x89, 0x11, 0xb6, 0x94, 0x17, 0x3b, 0xc2, 0xc1, 0xf8, 0x18, 0xf0,
  0xc2, 0xa4, 0x84, 0x44, 0x58, 0x49, 0x4c, 0x54, 0x07, 0x00, 0x00, 0x60,
  0x00, 0x00, 0x00, 0xd5, 0x01, 0x00, 0x00, 0x44, 0x58, 0x49, 0x4c, 0x00,
  0x01, 0x00, 0x00, 0x10, 0x00, 0x00, 0x00, 0x3c, 0x07, 0x00, 0x00, 0x42,
  0x43, 0xc0, 0xde, 0x21, 0x0c, 0x00, 0x00, 0xcc, 0x01, 0x00, 0x00, 0x0b,
  0x82, 0x20, 0x00, 0x02, 0x00, 0x00, 0x00, 0x13, 0x00, 0x00, 0x00, 0x07,
  0x81, 0x23, 0x91, 0x41, 0xc8, 0x04, 0x49, 0x06, 0x10, 0x32, 0x39, 0x92,
  0x01, 0x84, 0x0c, 0x25, 0x05, 0x08, 0x19, 0x1e, 0x04, 0x8b, 0x62, 0x80,
  0x14, 0x45, 0x02, 0x42, 0x92, 0x0b, 0x42, 0xa4, 0x10, 0x32, 0x14, 0x38,
  0x08, 0x18, 0x4b, 0x0a, 0x32, 0x52, 0x88, 0x48, 0x90, 0x14, 0x20, 0x43,
  0x46, 0x88, 0xa5, 0x00, 0x19, 0x32, 0x42, 0xe4, 0x48, 0x0e, 0x90, 0x91,
  0x22, 0xc4, 0x50, 0x41, 0x51, 0x81, 0x8c, 0xe1, 0x83, 0xe5, 0x8a, 0x04,
  0x29, 0x46, 0x06, 0x51, 0x18, 0x00, 0x00, 0x08, 0x00, 0x00, 0x00, 0x1b,
  0x8c, 0xe0, 0xff, 0xff, 0xff, 0xff, 0x07, 0x40, 0x02, 0xa8, 0x0d, 0x84,
  0xf0, 0xff, 0xff, 0xff, 0xff, 0x03, 0x20, 0x6d, 0x30, 0x86, 0xff, 0xff,
  0xff, 0xff, 0x1f, 0x00, 0x09, 0xa8, 0x00, 0x49, 0x18, 0x00, 0x00, 0x03,
  0x00, 0x00, 0x00, 0x13, 0x82, 0x60, 0x42, 0x20, 0x4c, 0x08, 0x06, 0x00,
  0x00, 0x00, 0x00, 0x89, 0x20, 0x00, 0x00, 0x43, 0x00, 0x00, 0x00, 0x32,
  0x22, 0x48, 0x09, 0x20, 0x64, 0x85, 0x04, 0x93, 0x22, 0xa4, 0x84, 0x04,
  0x93, 0x22, 0xe3, 0x84, 0xa1, 0x90, 0x14, 0x12, 0x4c, 0x8a, 0x8c, 0x0b,
  0x84, 0xa4, 0x4c, 0x10, 0x68, 0x23, 0x00, 0x25, 0x00, 0x14, 0x66, 0x00,
  0xe6, 0x08, 0xc0, 0x60, 0x8e, 0x00, 0x29, 0xc6, 0x20, 0x84, 0x14, 0x42,
  0xa6, 0x18, 0x80, 0x10, 0x52, 0x06, 0xa1, 0x9b, 0x86, 0xcb, 0x9f, 0xb0,
  0x87, 0x90, 0xfc, 0x95, 0x90, 0x56, 0x62, 0xf2, 0x8b, 0xdb, 0x46, 0xc5,
  0x18, 0x63, 0x10, 0x2a, 0xf7, 0x0c, 0x97, 0x3f, 0x61, 0x0f, 0x21, 0xf9,
  0x21, 0xd0, 0x0c, 0x0b, 0x81, 0x82, 0x55, 0x18, 0x45, 0x18, 0x1b, 0x63,
  0x0c, 0x42, 0xc8, 0xa0, 0x36, 0x47, 0x10, 0x14, 0x83, 0x91, 0x42, 0xc8,
  0x23, 0x38, 0x10, 0x30, 0x8c, 0x40, 0x0c, 0x33, 0xb5, 0xc1, 0x38, 0xb0,
  0x43, 0x38, 0xcc, 0xc3, 0x3c, 0xb8, 0x01, 0x2d, 0x94, 0x03, 0x3e, 0xd0,
  0x43, 0x3d, 0xc8, 0x43, 0x39, 0xc8, 0x01, 0x29, 0xf0, 0x81, 0x3d, 0x94,
  0xc3, 0x38, 0xd0, 0xc3, 0x3b, 0xc8, 0x03, 0x1f, 0x98, 0x03, 0x3b, 0xbc,
  0x43, 0x38, 0xd0, 0x03, 0x1b, 0x80, 0x01, 0x1d, 0xf8, 0x01, 0x18, 0xf8,
  0x81, 0x1e, 0xe8, 0x41, 0x3b, 0xa4, 0x03, 0x3c, 0xcc, 0xc3, 0x2f, 0xd0,
  0x43, 0x3e, 0xc0, 0x43, 0x39, 0xa0, 0x80, 0xcc, 0x24, 0x06, 0xe3, 0xc0,
  0x0e, 0xe1, 0x30, 0x0f, 0xf3, 0xe0, 0x06, 0xb4, 0x50, 0x0e, 0xf8, 0x40,
  0x0f, 0xf5, 0x20, 0x0f, 0xe5, 0x20, 0x07, 0xa4, 0xc0, 0x07, 0xf6, 0x50,
  0x0e, 0xe3, 0x40, 0x0f, 0xef, 0x20, 0x0f, 0x7c, 0x60, 0x0e, 0xec, 0xf0,
  0x0e, 0xe1, 0x40, 0x0f, 0x6c, 0x00, 0x06, 0x74, 0xe0, 0x07, 0x60, 0xe0,
  0x07, 0x48, 0x98, 0x94, 0xea, 0x4d, 0xd2, 0x14, 0x51, 0xc2, 0xe4, 0xb3,
  0x00, 0xf3, 0x2c, 0x44, 0xc4, 0x4e, 0xc0, 0x44, 0xa0, 0x80, 0xd0, 0x4d,
  0x06, 0x02, 0x00, 0x13, 0x14, 0x72, 0xc0, 0x87, 0x74, 0x60, 0x87, 0x36,
  0x68, 0x87, 0x79, 0x68, 0x03, 0x72, 0xc0, 0x87, 0x0d, 0xaf, 0x50, 0x0e,
  0x6d, 0xd0, 0x0e, 0x7a, 0x50, 0x0e, 0x6d, 0x00, 0x0f, 0x7a, 0x30, 0x07,
  0x72, 0xa0, 0x07, 0x73, 0x20, 0x07, 0x6d, 0x90, 0x0e, 0x71, 0xa0, 0x07,
  0x73, 0x20, 0x07, 0x6d, 0x90, 0x0e, 0x78, 0xa0, 0x07, 0x73, 0x20, 0x07,
  0x6d, 0x90, 0x0e, 0x71, 0x60, 0x07, 0x7a, 0x30, 0x07, 0x72, 0xd0, 0x06,
  0xe9, 0x30, 0x07, 0x72, 0xa0, 0x07, 0x73, 0x20, 0x07, 0x6d, 0x90, 0x0e,
  0x76, 0x40, 0x07, 0x7a, 0x60, 0x07, 0x74, 0xd0, 0x06, 0xe6, 0x10, 0x07,
  0x76, 0xa0, 0x07, 0x73, 0x20, 0x07, 0x6d, 0x60, 0x0e, 0x73, 0x20, 0x07,
  0x7a, 0x30, 0x07, 0x72, 0xd0, 0x06, 0xe6, 0x60, 0x07, 0x74, 0xa0, 0x07,
  0x76, 0x40, 0x07, 0x6d, 0xe0, 0x0e, 0x78, 0xa0, 0x07, 0x71, 0x60, 0x07,
  0x7a, 0x30, 0x07, 0x72, 0xa0, 0x07, 0x76, 0x40, 0x07, 0x43, 0x9e, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x86, 0x3c,
  0x06, 0x10, 0x00, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x0c,
  0x79, 0x10, 0x20, 0x00, 0x04, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x18, 0xf2, 0x34, 0x40, 0x00, 0x0c, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x30, 0xe4, 0x81, 0x80, 0x00, 0x18, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x20, 0x0b, 0x04, 0x00, 0x00, 0x0f, 0x00, 0x00, 0x00, 0x32,
  0x1e, 0x98, 0x14, 0x19, 0x11, 0x4c, 0x90, 0x8c, 0x09, 0x26, 0x47, 0xc6,
  0x04, 0x43, 0x22, 0x25, 0x30, 0x02, 0x50, 0x0c, 0x45, 0x50, 0x12, 0x65,
  0x50, 0x1e, 0xe5, 0x40, 0xa5, 0x24, 0x46, 0x00, 0x8a, 0xa0, 0x10, 0x0a,
  0x84, 0xec, 0x0c, 0x00, 0xe1, 0x19, 0x00, 0xca, 0x63, 0x31, 0x0a, 0x11,
  0x08, 0xc4, 0x13, 0x08, 0x04, 0xf0, 0x3c, 0x00, 0x00, 0x00, 0x00, 0x79,
  0x18, 0x00, 0x00, 0x67, 0x00, 0x00, 0x00, 0x1a, 0x03, 0x4c, 0x90, 0x46,
  0x02, 0x13, 0x44, 0x35, 0x18, 0x63, 0x0b, 0x73, 0x3b, 0x03, 0xb1, 0x2b,
  0x93, 0x9b, 0x4b, 0x7b, 0x73, 0x03, 0x99, 0x71, 0xb9, 0x01, 0x41, 0xa1,
  0x0b, 0x3b, 0x9b, 0x7b, 0x91, 0x2a, 0x62, 0x2a, 0x0a, 0x9a, 0x2a, 0xfa,
  0x9a, 0xb9, 0x81, 0x79, 0x31, 0x4b, 0x73, 0x0b, 0x63, 0x4b, 0xd9, 0x10,
  0x04, 0x13, 0x04, 0xa2, 0x98, 0x20, 0x10, 0xc6, 0x06, 0x61, 0x20, 0x26,
  0x08, 0xc4, 0xb1, 0x41, 0x18, 0x0c, 0x0a, 0x70, 0x73, 0x1b, 0x06, 0xc4,
  0x20, 0x26, 0x08, 0x96, 0x44, 0x60, 0x82, 0x40, 0x20, 0x13, 0x04, 0x22,
  0xd9, 0x20, 0x10, 0xcd, 0x86, 0x84, 0x50, 0x16, 0x82, 0x18, 0x18, 0xc2,
  0xd9, 0x10, 0x3c, 0x13, 0x04, 0x6c, 0xda, 0x80, 0x10, 0xd1, 0x42, 0x10,
  0x03, 0x01, 0x6c, 0x08, 0xa4, 0x0d, 0x04, 0x04, 0x00, 0xd3, 0x04, 0x21,
  0xa3, 0x36, 0x04, 0xd5, 0x04, 0x41, 0x00, 0xc8, 0x41, 0x4d, 0x4d, 0xad,
  0xa5, 0xb9, 0xb9, 0x95, 0x91, 0x59, 0x95, 0xc9, 0xd1, 0x95, 0xe1, 0x31,
  0xa5, 0x9d, 0xa1, 0xd1, 0xa5, 0xb9, 0x9d, 0x39, 0xbd, 0x19, 0xbd, 0x9d,
  0xb1, 0x18, 0x7a, 0x62, 0x7a, 0x92, 0x9a, 0x20, 0x14, 0xcd, 0x04, 0xa1,
  0x70, 0x36, 0x04, 0xc4, 0x04, 0xa1, 0x78, 0x26, 0x08, 0x05, 0x34, 0x41,
  0x20, 0x94, 0x09, 0x02, 0xb1, 0x6c, 0x10, 0x3e, 0x30, 0xd8, 0xb0, 0x10,
  0x99, 0xb6, 0x71, 0xdd, 0xe0, 0x11, 0x5b, 0x18, 0x6c, 0x08, 0x86, 0x09,
  0x02, 0xc1, 0x6c, 0x10, 0x3e, 0x32, 0xd8, 0xb0, 0x0c, 0x99, 0xb6, 0x8d,
  0x41, 0x37, 0x78, 0xc3, 0x56, 0x06, 0x44, 0xa8, 0x8a, 0xb0, 0x86, 0x9e,
  0x9e, 0xa4, 0x88, 0x36, 0x08, 0xdf, 0xb7, 0x61, 0x61, 0xce, 0x40, 0xdb,
  0xb8, 0x6e, 0xe8, 0x98, 0x0d, 0x0d, 0x36, 0x0c, 0x62, 0x60, 0x06, 0x69,
  0xc0, 0x64, 0xca, 0xea, 0x8b, 0x2a, 0x4c, 0xee, 0xac, 0x8c, 0x6e, 0x82,
  0x50, 0x44, 0x1b, 0x16, 0x62, 0x0d, 0x34, 0x36, 0xe0, 0xb6, 0xc1, 0x23,
  0xb6, 0x30, 0xd8, 0x10, 0xb4, 0xc1, 0x86, 0x41, 0x0d, 0xdc, 0x00, 0xd8,
  0x50, 0x5c, 0xd8, 0x1b, 0x50, 0x40, 0x15, 0x36, 0x36, 0xbb, 0x36, 0x97,
  0x34, 0xb2, 0x32, 0x37, 0xba, 0x29, 0x41, 0x50, 0x85, 0x0c, 0xcf, 0xc5,
  0xae, 0x4c, 0x6e, 0x2e, 0xed, 0xcd, 0x6d, 0x4a, 0x40, 0x34, 0x21, 0xc3,
  0x73, 0xb1, 0x0b, 0x63, 0xb3, 0x2b, 0x93, 0x9b, 0x12, 0x18, 0x75, 0xc8,
  0xf0, 0x5c, 0xe6, 0xd0, 0xc2, 0xc8, 0xca, 0xe4, 0x9a, 0xde, 0xc8, 0xca,
  0xd8, 0xa6, 0x04, 0x48, 0x19, 0x32, 0x3c, 0x17, 0xb9, 0xb2, 0xb9, 0xb7,
  0x3a, 0xb9, 0xb1, 0xb2, 0xb9, 0x29, 0xc1, 0x54, 0x87, 0x0c, 0xcf, 0xc5,
  0x2e, 0xad, 0xec, 0x2e, 0x89, 0x6c, 0x8a, 0x2e, 0x8c, 0xae, 0x6c, 0x4a,
  0x50, 0xd5, 0x21, 0xc3, 0x73, 0x29, 0x73, 0xa3, 0x93, 0xcb, 0x83, 0x7a,
  0x4b, 0x73, 0xa3, 0x9b, 0x9b, 0x12, 0xbc, 0x01, 0x00, 0x00, 0x00, 0x79,
  0x18, 0x00, 0x00, 0x4c, 0x00, 0x00, 0x00, 0x33, 0x08, 0x80, 0x1c, 0xc4,
  0xe1, 0x1c, 0x66, 0x14, 0x01, 0x3d, 0x88, 0x43, 0x38, 0x84, 0xc3, 0x8c,
  0x42, 0x80, 0x07, 0x79, 0x78, 0x07, 0x73, 0x98, 0x71, 0x0c, 0xe6, 0x00,
  0x0f, 0xed, 0x10, 0x0e, 0xf4, 0x80, 0x0e, 0x33, 0x0c, 0x42, 0x1e, 0xc2,
  0xc1, 0x1d, 0xce, 0xa1, 0x1c, 0x66, 0x30, 0x05, 0x3d, 0x88, 0x43, 0x38,
  0x84, 0x83, 0x1b, 0xcc, 0x03, 0x3d, 0xc8, 0x43, 0x3d, 0x8c, 0x03, 0x3d,
  0xcc, 0x78, 0x8c, 0x74, 0x70, 0x07, 0x7b, 0x08, 0x07, 0x79, 0x48, 0x87,
  0x70, 0x70, 0x07, 0x7a, 0x70, 0x03, 0x76, 0x78, 0x87, 0x70, 0x20, 0x87,
  0x19, 0xcc, 0x11, 0x0e, 0xec, 0x90, 0x0e, 0xe1, 0x30, 0x0f, 0x6e, 0x30,
  0x0f, 0xe3, 0xf0, 0x0e, 0xf0, 0x50, 0x0e, 0x33, 0x10, 0xc4, 0x1d, 0xde,
  0x21, 0x1c, 0xd8, 0x21, 0x1d, 0xc2, 0x61, 0x1e, 0x66, 0x30, 0x89, 0x3b,
  0xbc, 0x83, 0x3b, 0xd0, 0x43, 0x39, 0xb4, 0x03, 0x3c, 0xbc, 0x83, 0x3c,
  0x84, 0x03, 0x3b, 0xcc, 0xf0, 0x14, 0x76, 0x60, 0x07, 0x7b, 0x68, 0x07,
  0x37, 0x68, 0x87, 0x72, 0x68, 0x07, 0x37, 0x80, 0x87, 0x70, 0x90, 0x87,
  0x70, 0x60, 0x07, 0x76, 0x28, 0x07, 0x76, 0xf8, 0x05, 0x76, 0x78, 0x87,
  0x77, 0x80, 0x87, 0x5f, 0x08, 0x87, 0x71, 0x18, 0x87, 0x72, 0x98, 0x87,
  0x79, 0x98, 0x81, 0x2c, 0xee, 0xf0, 0x0e, 0xee, 0xe0, 0x0e, 0xf5, 0xc0,
  0x0e, 0xec, 0x30, 0x03, 0x62, 0xc8, 0xa1, 0x1c, 0xe4, 0xa1, 0x1c, 0xcc,
  0xa1, 0x1c, 0xe4, 0xa1, 0x1c, 0xdc, 0x61, 0x1c, 0xca, 0x21, 0x1c, 0xc4,
  0x81, 0x1d, 0xca, 0x61, 0x06, 0xd6, 0x90, 0x43, 0x39, 0xc8, 0x43, 0x39,
  0x98, 0x43, 0x39, 0xc8, 0x43, 0x39, 0xb8, 0xc3, 0x38, 0x94, 0x43, 0x38,
  0x88, 0x03, 0x3b, 0x94, 0xc3, 0x2f, 0xbc, 0x83, 0x3c, 0xfc, 0x82, 0x3b,
  0xd4, 0x03, 0x3b, 0xb0, 0xc3, 0x0c, 0xc4, 0x21, 0x07, 0x7c, 0x70, 0x03,
  0x7a, 0x28, 0x87, 0x76, 0x80, 0x87, 0x19, 0xd1, 0x43, 0x0e, 0xf8, 0xe0,
  0x06, 0xe4, 0x20, 0x0e, 0xe7, 0xe0, 0x06, 0xf6, 0x10, 0x0e, 0xf2, 0xc0,
  0x0e, 0xe1, 0x90, 0x0f, 0xef, 0x50, 0x0f, 0xf4, 0x00, 0x00, 0x00, 0x71,
  0x20, 0x00, 0x00, 0x17, 0x00, 0x00, 0x00, 0x06, 0xc0, 0xa5, 0x2c, 0xab,
  0x20, 0x4d, 0x43, 0x0c, 0x2f, 0x11, 0x4d, 0xc4, 0x55, 0x22, 0xc6, 0x31,
  0x21, 0x8d, 0x71, 0x3a, 0x9f, 0x63, 0x18, 0x81, 0x34, 0x5c, 0xbe, 0xf3,
  0xf8, 0x42, 0x44, 0x00, 0x13, 0x11, 0x02, 0xcd, 0xb0, 0x10, 0x16, 0x30,
  0x0d, 0x97, 0xef, 0x3c, 0xfe, 0xe2, 0x00, 0x83, 0xd8, 0x3c, 0xd4, 0xe4,
  0x17, 0xb7, 0x6d, 0x03, 0xd0, 0x70, 0xf9, 0xce, 0xe3, 0x4b, 0x00, 0xf3,
  0x2c, 0x84, 0x5f, 0xdc, 0xb6, 0x09, 0x54, 0xc3, 0xe5, 0x3b, 0x8f, 0x2f,
  0x4d, 0x4e, 0x44, 0xa0, 0xd4, 0xf4, 0x50, 0x93, 0x5f, 0xdc, 0x36, 0x00,
  0x00, 0x00, 0x00, 0x61, 0x20, 0x00, 0x00, 0x4b, 0x00, 0x00, 0x00, 0x13,
  0x04, 0x41, 0x2c, 0x10, 0x00, 0x00, 0x00, 0x05, 0x00, 0x00, 0x00, 0xf4,
  0x46, 0x00, 0x88, 0xcc, 0x00, 0x14, 0x42, 0x29, 0x94, 0x5c, 0xe1, 0x51,
  0x29, 0x81, 0x32, 0xa0, 0x31, 0x03, 0x00, 0x23, 0x06, 0x09, 0x00, 0x82,
  0x60, 0x00, 0x69, 0x05, 0x84, 0x61, 0xc9, 0x88, 0x41, 0x02, 0x80, 0x20,
  0x18, 0x40, 0x9b, 0x31, 0x64, 0x99, 0x32, 0x62, 0x90, 0x00, 0x20, 0x08,
  0x06, 0xc6, 0x97, 0x60, 0x9a, 0xa4, 0x8c, 0x18, 0x24, 0x00, 0x08, 0x82,
  0x81, 0x01, 0x06, 0x4a, 0xb6, 0x19, 0xcb, 0x88, 0x41, 0x02, 0x80, 0x20,
  0x18, 0x18, 0x61, 0xb0, 0x74, 0x1c, 0xc5, 0x8c, 0x18, 0x24, 0x00, 0x08,
  0x82, 0x81, 0x21, 0x06, 0x8c, 0xd7, 0x21, 0xcd, 0x88, 0x41, 0x02, 0x80,
  0x20, 0x18, 0x18, 0x63, 0xd0, 0x7c, 0x5e, 0xe5, 0x8c, 0x18, 0x24, 0x00,
  0x08, 0x82, 0x81, 0x41, 0x06, 0xce, 0xf7, 0x5d, 0xcf, 0x88, 0x41, 0x02,
  0x80, 0x20, 0x18, 0x18, 0x65, 0xf0, 0x80, 0x01, 0x18, 0x2c, 0xd0, 0x88,
  0x41, 0x02, 0x80, 0x20, 0x18, 0x18, 0x66, 0x00, 0x85, 0x41, 0x18, 0x60,
  0xd1, 0x88, 0x41, 0x02, 0x80, 0x20, 0x18, 0x18, 0x67, 0x10, 0x89, 0x81,
  0x18, 0x30, 0xd2, 0x88, 0xc1, 0x03, 0x80, 0x20, 0x18, 0x34, 0x66, 0xf0,
  0x2c, 0x4a, 0x82, 0x30, 0xcc, 0x18, 0x8c, 0xc1, 0xc4, 0x8c, 0x26, 0x04,
  0xc0, 0x68, 0x82, 0x10, 0x8c, 0x26, 0x0c, 0xc2, 0x68, 0x02, 0x31, 0x18,
  0x91, 0xc8, 0xc7, 0x88, 0x44, 0x3e, 0x46, 0x24, 0xf2, 0x31, 0x22, 0x91,
  0x8f, 0x05, 0x90, 0x7c, 0x4c, 0x80, 0xe4, 0x63, 0x03, 0x24, 0x1f, 0x1b,
  0x0e, 0xf8, 0xd8, 0x70, 0xc0, 0xc7, 0x86, 0x03, 0x3e, 0x23, 0x06, 0x09,
  0x00, 0x82, 0x60, 0x80, 0xd8, 0x01, 0x18, 0xc8, 0x81, 0x1c, 0xa8, 0xc1,
  0x30, 0x62, 0x90, 0x00, 0x20, 0x08, 0x06, 0x88, 0x1d, 0x80, 0x81, 0x1c,
  0xc8, 0x41, 0x27, 0x8c, 0x18, 0x24, 0x00, 0x08, 0x82, 0x01, 0x62, 0x07,
  0x60, 0x20, 0x07, 0x72, 0x90, 0x06, 0xc1, 0x88, 0x41, 0x02, 0x80, 0x20,
  0x18, 0x20, 0x76, 0x00, 0x06, 0x72, 0x20, 0x07, 0xdc, 0x81, 0x00, 0x00,
  0x00, 0x00, 0x00
};