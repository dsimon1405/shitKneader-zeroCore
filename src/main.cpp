#include <ZC/main/ZC_main.h>
#include <ZC/Video/ZC_Video.h>

#include <ZC/Video/OpenGL/Shader/ZC_ShaderLoader.h>
#include <ZC/Video/OpenGL/Shader/ZC_Shader.h>
#include <ZC/Video/OpenGL/VAO/ZC_VAO.h>
#include <ZC/Video/OpenGL/ZC_VBO.h>

#include <ZC/Tools/Time/ZC_Clock.h>

#include <ZC/Audio/ZC_Audio.h>
#include <ZC/Audio/ZC_Sounds.h>

#include <SK_AssetsPaths.h>

#include <ZC/Tools/Math/ZC_Mat.h>
 #include <ZC/Tools/Console/ZC_cout.h>
class A
{
public:
   A() = default;
   explicit A(int _a) : a(_a){
    ZC_cout("A ctr " + std::to_string(a));
    }
   A(const A& _a)
    // = delete;
    : a(_a.a)
   {
    ZC_cout("A() copy");
    }
   A& operator = (const A& _a)
    // = delete;
   {a = _a.a; 
   ZC_cout("A = copy");
    return *this;}
   A(A&& _a)  noexcept : a(_a.a){_a.a = 0;
   ZC_cout("A() move");
   }
   A& operator = (A&& _a) noexcept {a = _a.a; _a.a = 0;
    ZC_cout("A = move");
     return *this;}
   virtual ~A(){
    ZC_cout("A dtr " + std::to_string(a));
    }

    // bool operator < (const A& _a) const {return a < _a.a;}
  //  virtual void Foo(){ZC_cout("A");}
   int a = 0;
protected:
private:
};
class B : public A
{
public:
   B() = delete;
   explicit B(int _a) : A(_a) {ZC_cout("B ctr");}
   B(const B& _a) : A(dynamic_cast<const A&>(_a)){ZC_cout("B() copy");}
   B& operator = (const B& _a){dynamic_cast<A&>(*this) = dynamic_cast<const A&>(_a); ZC_cout("B = copy"); return *this;}
   B(B&& _a)  noexcept : A(dynamic_cast<A&&>(_a)){ZC_cout("B() move");}
   B& operator = (B&& _a) noexcept {dynamic_cast<A&>(*this) = dynamic_cast<A&&>(_a); ZC_cout("B = move"); return *this;}
   ~B() override{ZC_cout("B dtr");}
};

// #include <matrix.hpp>
// #include <gtc/matrix_transform.hpp>

template<typename T>
void FillMat(T& mat)
{
  float a = 0.0f;
  for (int i = 0; i < 4; i++)
  {
      for (int j = 0; j < 4; j++)
      {
          mat[i][j] = ++a;
      }
  }
}

// bool EqualMat(const ZC_Mat4<float>& mat1, const glm::mat4 mat2)
// {
//   for (int i = 0; i < 4; i++)
//   {
//       for (int j = 0; j < 4; j++)
//       {
//           if (mat1[i][j] != mat2[i][j]) return false;
//       }
//   }
//   return true;
// }

template<typename T>
struct S
{
  constexpr S(T _t) : t(_t){}
  constexpr S<T>& operator += (const S<T>& s)
  {
    t += s.t;
    return *this;
  }
  constexpr S<T> operator + (const S<T>& s) const
  {
    S<T> k(t + s.t);
    return k;
    // return S<T>(*this) += s;
  }

  T t;
};

template<typename T>
constexpr S<T> Foo(S<T> s1, S<T> s2)
{
  int a = 2;
  s1.t += a;
  return s1 + s2;
}
//  579,1 кБ (579 144 байта)
int ZC_main()
{
  constexpr ZC_Vec3 v1(1.f,2.f,3.f);
  constexpr ZC_Vec3 v2(1.1f,2.1f,3.1f);
  constexpr auto v3 = v1 + v2;

    ZC_upWindow window = ZC_Video::MakeWindow("lolka", 640, 480);
    
     ZC_Sounds::LoadWAV("lp", SK_Path_sounds_lp);
     ZC_upSound lp = ZC_Sounds::GetSound("lp");
     ZC_Sounds::LoadWAV("Airplanes", SK_Path_sounds_Airplanes);
     ZC_upSound airplanes = ZC_Sounds::GetSound("Airplanes");
     ZC_Audio::OpenAudioStream(ZC_AudioSet(ZC_AudioSet::Channels::Stereo, 44100, ZC_AudioSet::BitsPerSample::S16));
     lp->Play();
     airplanes->Play();

     ZC_VAOConfig vaoConfig;
     vaoConfig.AddFormat(ZC_VAOConfig::Format(0, 3, GL_FLOAT, GL_FALSE, 0))
             ->AddFormat({1, 3, GL_FLOAT, GL_FALSE, sizeof(float) * 3});
     ZC_VAO* vao = ZC_VAO::GetVAO(vaoConfig);

   ZC_DynamicArray<float> vertices;
   vertices.size = 24;
   vertices.pArray = new float[vertices.size]{
       0.f, 0.f, 1.0f, 0.0f, 0.0f, 0.0f,   // top left
       0.f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f,  // bottom left
       1.0f, 0.0f, 1.0f, 1.0f, 0.0f, 0.0f,  // top right
       1.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f  // bottom right
   };
     ZC_VBO* vbo = ZC_VBO::CreateVBO();
     vbo->BufferData(sizeof(GLfloat) * vertices.size, GL_STATIC_DRAW);
     vbo->BufferSubData(sizeof(float) * 0, std::move(vertices));

     ZC_Shader* shader = ZC_Shader::CreateShader("test", ZC_ShaderLoader::LoadShaderCode(SK_Path_shaders_testVS, SK_Path_shaders_testFS));

     auto view = ZC_Mat::LookAt(ZC_Vec3(0.f,-50.f,0.f),{0.f,0.f,0.f},{0.f,0.f,1.f});
     auto perspective = ZC_Mat::Perspective(45.0f, static_cast<float>(window->GetWidth() / window->GetHeight()), 0.1f, 100.0f);
    
    // auto v = glm::lookAt(glm::vec3(0.f,3.f,2.f),{0.f,0.f,0.f},{0.f,0.f,1.f});
    // auto p = glm::perspective(glm::radians(45.f), static_cast<float>(window->GetWidth() / window->GetHeight()), 0.1f, 100.0f);
    // bool q1 = EqualMat(view,v);
    // bool q2 = EqualMat(perspective,p);

    // model.Translate({0.5f,0.f,0.5f}).Translate({10.f,0.f,0.f}).Translate({-0.5f,0.f,-0.5f});
    // model.Rotate(-30.f, {0,0,1});
    unsigned long count = 0;
    ZC_Clock c;
          srand(time(0));
     while (true)
     {
         if (!window->HandleEvents())
         {
            break;
         }
        
         window->Clear();

          shader->Use();
          shader->SetUniformMatrix4fv("projection", perspective.Begin());
          shader->SetUniformMatrix4fv("view", view.Begin());
        c.Restart<ZC_Seconds>();
      ZC_Mat4 model(1.0f);
    model.Translate({-0.5f,0.f,-0.5f}).Translate({-0.5f,0.f,-0.5f});
         shader->SetUniformMatrix4fv("model", model.Begin());
         vao->DrawArrays(vbo, 0, GL_TRIANGLE_STRIP, 4);
        
        window->SwapBuffer();

        ++count;
        if (c.Time<ZC_Seconds>() >= 1)
        {
          ZC_cout(std::to_string(count));
          count = 0;
          c.Start();
        }
     }
    ZC_Audio::CloseAudioStream();
     return 0;
}