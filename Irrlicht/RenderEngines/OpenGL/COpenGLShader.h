#ifndef __C_VIDEO_OPEN_GL_SHADER_H_INCLUDED__
#define __C_VIDEO_OPEN_GL_SHADER_H_INCLUDED__

#include "IrrCompileConfig.h"

#include "SIrrCreationParameters.h"

namespace irr
{
    class CIrrDeviceWin32;
    class CIrrDeviceLinux;
    class CIrrDeviceSDL;
    class CIrrDeviceMacOSX;
}

#ifdef _IRR_COMPILE_WITH_OPENGL_

#include "RenderEngines/General/CIrrShader.h"
#include "COpenGLExtensionHandler.h"
#include "COpenGLHardwareBuffer.h"

#include <vector>

#ifdef _IRR_COMPILE_WITH_CG_
#include "Cg/cg.h"
#endif

namespace irr
{
    namespace scene
    {
        enum E_HARDWARE_MAPPING;
    };

    namespace video
    {
        class GLArbShader;
        class GLSLGpuShader;
        class COpenGLDriver;
        class COpenGLTexture;
        class COpenGLHardwareBuffer;

        //struct CGlslBufferDesc;
        //
        //struct CGlslVariableDesc
        //{
        //    CGlslBufferDesc* BufferDesc;
        //    ShaderVariableDescriptor varDesc;
        //    std::string name;                   // Not qualified name
        //    std::vector<CGlslVariableDesc> members;
        //    //u32 type;
        //    u32 offset;
        //    u32 blockIndex;
        //    u32 arrayStride;
        //    u32 matrixStride;
        //    u32 elementSize;
        //    u32 dataSize;
        //    //SSBO
        //    u32 toplevel_arraysize;
        //    u32 toplevel_arraystride;
        //    bool isRowMajor;
        //};
        //
        //struct CGlslBufferDesc
        //{
        //    ~CGlslBufferDesc()
        //    {
        //
        //    }
        //
        //    u32 binding;
        //    u32 dataSize;
        //    ShaderVariableDescriptor varDesc;
        //    COpenGLHardwareBuffer* m_constantBuffer = nullptr;
        //    u32 ChangeId;
        //    u32 ChangeStartOffset;
        //    u32 ChangeEndOffset;
        //    E_SHADER_TYPES shaderType : 8;
        //    scene::E_HARDWARE_MAPPING constantMapping : 8;
        //    std::vector<CGlslVariableDesc> members;
        //    core::array<char> DataBuffer;
        //
        //    COpenGLHardwareBuffer* getHardwareBuffer() const { return m_constantBuffer; }
        //    scene::E_HARDWARE_MAPPING getHardwareMappingHint() const { return constantMapping; }
        //    void setHardwareMappingHint(scene::E_HARDWARE_MAPPING value) { constantMapping = value; }
        //    u32 getChangeId() const { return ChangeId; }
        //};

        class GLShader : public CNullShader
        {
        protected:
            u32 programId;
            GLenum glShaderType;

        public:
            GLShader(video::IVideoDriver* context, E_SHADER_LANG type, u32 _programId)
                : CNullShader(context, type)
                , programId(_programId)
            {
            }

            virtual ~GLShader()
            {
            }

            u32 getProgramId() const { return programId; }

            COpenGLDriver* getDriverOGL();

            virtual GLSLGpuShader* ToGLSL() { return nullptr; }
            virtual GLArbShader* ToASM() { return nullptr; }
        };

        class GLArbShader : public GLShader
        {
            GLenum glShaderType;
        public:
            explicit GLArbShader(video::IVideoDriver* context, u32 _programId);
            virtual ~GLArbShader();

            void addShaderFile(u32 _glShaderType, const char* pFilename);

            virtual void Init() {}

             GLArbShader* ToASM() _IRR_OVERRIDE_ { return this; }
        };

        class GLSLGpuShader : public GLShader
        {
        public:
            explicit GLSLGpuShader(video::IVideoDriver* context, u32 _programId);
            virtual ~GLSLGpuShader();

            //virtual void compile() override;
            virtual void Init() _IRR_OVERRIDE_ {}

            void addShaderFile(GLSLGpuShader*, u32 shaderType, System::IO::IFileReader* pFilename, std::list<u32>& ShaderObjList);
            void compile(GLSLGpuShader*, std::list<u32>& ShaderObjList);
            void buildShaderVariableDescriptor();
            void ReflParseStruct(irr::video::SConstantBuffer* buffdesc, irr::video::IShaderVariable* parent, const u32* memberParams, std::vector<irr::video::IShaderVariable*>& Variables, std::string namePrefix);

            GLSLGpuShader* ToGLSL() _IRR_OVERRIDE_ { return this; }
        };

        //struct ShaderGenericValuesBuffer : public video::IShaderDataBuffer
        //{
        //    struct ATTR_ALIGNED(16) MatrixBufferType
        //    {
        //        core::matrix4 world;
        //        core::matrix4 view;
        //        core::matrix4 projection;
        //    };
        //
        //    struct ATTR_ALIGNED(16) Light
        //    {
        //        float Position[4];
        //        float Atten[4];
        //        irr::video::SColorf Diffuse;
        //        irr::video::SColorf Specular;
        //        irr::video::SColorf Ambient;
        //        float Range;
        //        float Falloff;
        //        float Theta;
        //        float Phi;
        //        int   Type;
        //
        //        bool operator==(const Light& other) const
        //        {
        //            return memcmp(this, &other, sizeof(Light)) == 0;
        //        }
        //
        //        bool operator!=(const Light& other) const
        //        {
        //            return memcmp(this, &other, sizeof(Light)) != 0;
        //        }
        //    };
        //
        //    struct ATTR_ALIGNED(16) Material
        //    {
        //        irr::video::SColorf    Ambient;
        //        irr::video::SColorf    Diffuse;
        //        irr::video::SColorf    Specular;
        //        irr::video::SColorf    Emissive;
        //        float     Shininess;
        //        int       Type;
        //        int       Flags;
        //
        //        bool operator==(const Material& other) const
        //        {
        //            return memcmp(this, &other, sizeof(Material)) == 0;
        //        }
        //
        //        bool operator!=(const Material& other) const
        //        {
        //            return memcmp(this, &other, sizeof(Material)) != 0;
        //        }
        //    };
        //
        //    struct ATTR_ALIGNED(16) PixelConstantBufferType
        //    {
        //        int         nTexture;
        //        int         AlphaTest;
        //        int         LightCount; // Number of lights enabled
        //        float       AlphaRef;
        //        Material    material;
        //        Light       lights[4];
        //    };
        //
        //    video::ShaderDataBufferElementObject<core::matrix4>* world;
        //    video::ShaderDataBufferElementObject<core::matrix4>* view;
        //    video::ShaderDataBufferElementObject<core::matrix4>* projection;
        //    video::ShaderDataBufferElementObject<core::matrix4>* textureMatrix1;
        //    video::ShaderDataBufferElementObject<core::matrix4>* textureMatrix2;
        //
        //    video::ShaderDataBufferElementObject<int>* nTexture;
        //    video::ShaderDataBufferElementObject<int>* AlphaTest;
        //    video::ShaderDataBufferElementObject<int>* LightCount;
        //    video::ShaderDataBufferElementObject<float>* AlphaRef;
        //    video::ShaderDataBufferElementObject<video::SColorf>* fogParams;
        //    video::ShaderDataBufferElementObject<video::SColorf>* fogColor;
        //    video::ShaderDataBufferElementObject<core::vector3df>* eyePositionVert;
        //    video::ShaderDataBufferElementObject<ShaderGenericValuesBuffer::Material>* ShaderMaterial;
        //    video::ShaderDataBufferElementArray<ShaderGenericValuesBuffer::Light>* ShaderLight;
        //
        //    core::vector3df viewMatrixTranslationCache;
        //
        //    ShaderGenericValuesBuffer(video::IShaderDataBuffer::E_UPDATE_TYPE updateType);
        //
        //    virtual ~ShaderGenericValuesBuffer();
        //
        //    virtual void InitializeFormShader(video::IShader* gpuProgram, void* Descriptor);
        //
        //    virtual void UpdateBuffer(video::IShader* gpuProgram, scene::IMeshBuffer* meshBuffer, scene::IMesh* mesh, scene::ISceneNode* node, u32 updateFlags);
        //};
    }
}

#endif //!_IRR_COMPILE_WITH_OPENGL_
#endif //!__C_VIDEO_OPEN_GL_SHADER_H_INCLUDED__