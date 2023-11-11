#include <ZC/main/ZC_main.h>
#include <ZC/Video/ZC_Video.h>

#include <ZC/Video/OpenGL/Shader/ZC_ShaderLoader.h>
#include <ZC/Video/OpenGL/Shader/ZC_Shader.h>
#include <ZC/Video/OpenGL/VAO/ZC_VAO.h>
#include <ZC/Video/OpenGL/ZC_VBO.h>

#include <ZC/Audio/ZC_Audio.h>
#include <ZC/Audio/ZC_Sounds.h>

//  #include <ZC/Tools/Console/ZC_cout.h>
// class A
// {
// public:
//    A() = delete;
//    A(const A& _a) : A(_a.a){ZC_cout("A() copy");}
//    A(A&& _a)  noexcept : A(_a.a){_a.a = 0;ZC_cout("A() move");}
//    A& operator = (const A& _a){a = _a.a; ZC_cout("A = copy"); return *this;}
//    A& operator = (A&& _a) noexcept {a = _a.a; _a.a = 0; ZC_cout("A = move"); return *this;}
//    virtual ~A(){ZC_cout("A dtr");}

//    virtual void Foo(){ZC_cout("A");}
// protected:
//    explicit A(int _a) : a(_a) {ZC_cout("A ctr");}
// private:
//    int a;
// };
// class B : public A
// {
// public:
//    B() = delete;
//    explicit B(int _a) : A(_a) {ZC_cout("B ctr");}
//    B(const B& _a) : A(dynamic_cast<const A&>(_a)){ZC_cout("B() copy");}
//    B& operator = (const B& _a){dynamic_cast<A&>(*this) = dynamic_cast<const A&>(_a); ZC_cout("B = copy"); return *this;}
//    B(B&& _a)  noexcept : A(dynamic_cast<A&&>(_a)){ZC_cout("B() move");}
//    B& operator = (B&& _a) noexcept {dynamic_cast<A&>(*this) = dynamic_cast<A&&>(_a); ZC_cout("B = move"); return *this;}
//    ~B() override{ZC_cout("B dtr");}
//    void Foo() override  {ZC_cout("B");}
// };

#include <ZC/Tools/ZC_DynamicArray.h>

class A : public ZC_DynamicArray<int>
{
public:
    A(const size_t& size)
        : ZC_DynamicArray<int>(size),
        a(size)
    {}

    A(A&& aa)
      : ZC_DynamicArray<int>(dynamic_cast<ZC_DynamicArray<int>&&>(aa))
    {
        a = aa.a;
    }

private:
    int a;
};

int ZC_main()
{
    ZC_upWindow window = ZC_Video::MakeWindow("lolka", 640, 480);

  ZC_Sounds::LoadWAV("lp", "sounds/lp.wav");
   ZC_upSound lp = ZC_Sounds::GetSound("lp");

   ZC_Sounds::LoadWAV("Airplanes", "sounds/Airplanes.wav");
   ZC_upSound airplanes = ZC_Sounds::GetSound("Airplanes");

   ZC_Audio::MakeAudioStream(ZC_AudioSet(ZC_AudioSet::Channels::Stereo, 44100, ZC_AudioSet::BitsPerSample::S16));

   lp->Play();
   airplanes->Play();

    ZC_VAOConfig vaoConfig;
    vaoConfig.AddFormat(ZC_VAOConfig::Format(0, 3, GL_FLOAT, GL_FALSE, 0))
            ->AddFormat({1, 3, GL_FLOAT, GL_FALSE, sizeof(float) * 3});
    ZC_VAO* vao = ZC_VAO::GetVAO(vaoConfig);

  float* vertices = new float[24]{
      0.f,  1.f, 0.0f, 0.0f, 0.0f, 0.0f,   // top left
      0.f, 0.f, 0.0f, 0.0f, 0.0f, 1.0f,  // bottom left
       1.f,  1.f, 0.0f, 1.0f, 0.0f, 0.0f,  // top right
       1.f, 0.f, 0.0f, 0.0f, 1.0f, 0.0f  // bottom right
  };
    ZC_VBO* vbo = ZC_VBO::CreateVBO();
    vbo->BufferData(sizeof(float) * 24, vertices, GL_STATIC_DRAW);
    vbo->BufferSubData(sizeof(float) * 0, sizeof(float) * 24, vertices);

  float* vertices1 = new float[24]{
      -1.f,  0.f, 0.0f, 0.0f, 0.0f, 0.0f,   // top left
      -1.f, -1.f, 0.0f, 0.0f, 0.0f, 1.0f,  // bottom left
       0.f,  0.f, 0.0f, 1.0f, 0.0f, 0.0f,  // top right
       0.f, -1.f, 0.0f, 0.0f, 1.0f, 0.0f  // bottom right
  };
  ZC_VBO* vbo1 = ZC_VBO::CreateVBO();
    vbo1->BufferData(sizeof(float) * 24, vertices1, GL_STATIC_DRAW);

    ZC_Shader* shader = ZC_Shader::CreateShader("test", ZC_ShaderLoader::LoadShaderCode("shaders/test.vs", "shaders/test.fs"));

     while (true)
     {
         if (!window->HandleEvents())
         {
             return 0;
         }
        
        window->Clear();

        shader->Use();

        vao->DrawArrays(vbo, 0, GL_TRIANGLE_STRIP, 4);
        vao->DrawArrays(vbo1, 0, GL_TRIANGLE_STRIP, 4);
        
        window->SwapBuffer();
     }
     
     return 0;
}