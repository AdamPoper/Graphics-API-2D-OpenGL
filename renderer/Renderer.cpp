#include "Renderer.h"
namespace ap {

    uint32_t Renderer::s_referenceCounter = 0;
    Renderer::Renderer(const Window* win)
        : m_renderTarget(win), m_camera(nullptr)
    {       
        s_referenceCounter++;
        assert(s_referenceCounter < 2); // there can only be one renderer        
        m_projection = glm::ortho(0.0f, m_renderTarget->Width(), m_renderTarget->Height(), 0.0f, -1.0f, 1.0f);
        m_view       = glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, 0.0f, 0.0f));
        m_vertexArray.push<float>(2); // positions
        m_vertexArray.push<float>(4); // color including alpha    
        m_vertexArray.push<float>(2); // texture coordinates
        m_vertexArray.push<float>(1); // texture slot
        m_vertexArray.push<float>(1); // yes or no has texture
        m_vertexBuffer  = new VertexBuffer();
        m_indexBuffer   = new IndexBuffer();       
        m_shaderProgram = new ShaderProgram("Source/renderer/shaders/VertexShader.shader", "Source/renderer/shaders/FragmentShader.shader");        
        m_vertexArray.Enable();        
        Blend();
        int samplers[32] = { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 26, 27, 28, 29, 30, 31 };
        m_shaderProgram->setUniform1iv(samplers, 32, "u_Texture");
        glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
    }
    Renderer::~Renderer()
    {
        s_referenceCounter--;
        delete m_vertexBuffer;
        delete m_indexBuffer;
        delete m_shaderProgram;        
    }
    void Renderer::Draw(Entity* ent)
    {
        // if circle add the individual triangles as entity pointers
        m_entities.push_back(ent);
    }
    void Renderer::onUpdate()
    {   
        //std::cout << __FILE__ << " " << glGetError() << " " << __LINE__ << std::endl;
        glClear(GL_COLOR_BUFFER_BIT);
        m_vertexBuffer->clearVertexBuffer();
        m_indexBuffer->clearIndexBuffer();
        if (m_camera != nullptr)
            m_view = m_camera->GetTranslation();
        m_MVP = m_projection * m_view;    
        for (auto& e : m_entities)
        {            
            e->setData();
            m_vertexBuffer->addVertexData(e->getData(), e->getNumVerticies());
            m_indexBuffer->updateIndicies(e->getNumIndicies());    
            if (e->hasTexture())  // only bind texture if the entity has one
            {                              
                e->getTexture()->Bind((uint32_t)e->getTextureIndex());
            }
        } 
        
        m_vertexBuffer->setDynamicGeometry();
        m_shaderProgram->addMatrix4fv(m_MVP, "u_MVP");
        glDrawElements(GL_TRIANGLES, m_indexBuffer->Count(), GL_UNSIGNED_INT, nullptr);
        m_entities.clear();
        //std::cout << __FILE__ << " " << glGetError() << " " << __LINE__ << std::endl;
    }
    void Renderer::Blend() const
    {
        glEnable(GL_BLEND);
        glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    }
    void Renderer::addCamera(Camera* cam)
    { 
        m_camera = cam;
    }
    void Renderer::RemoveCamera()
    {
        m_camera = nullptr;
    }
    void Renderer::SetRenderClearColor(const Vec3f& color) const
    {
        glClearColor(color.r, color.g, color.g, 1.0f);
    }
    Vec4f Renderer::Color::Blue   = { 0.0f, 0.0f, 1.0f, 1.0f };
    Vec4f Renderer::Color::Red    = { 1.0f, 0.0f, 0.0f, 1.0f };
    Vec4f Renderer::Color::Green  = { 0.0f, 1.0f, 0.0f, 1.0f };
    Vec4f Renderer::Color::Cyan   = { 0.0f, 1.0f, 1.0f, 1.0f };
    Vec4f Renderer::Color::Pink   = { 1.0f, 0.0f, 1.0f, 1.0f };
    Vec4f Renderer::Color::Purple = { 0.8f, 0.0f, 0.8f, 1.0f };
    Vec4f Renderer::Color::White  = { 1.0f, 1.0f, 1.0f, 1.0f };
    Vec4f Renderer::Color::Gray   = { 0.5f, 0.5f, 0.5f, 1.0f };
    Vec4f Renderer::Color::Black  = { 0.0f, 0.0f, 0.0f, 1.0f };
    Vec4f Renderer::Color::Yellow = { 1.0f, 1.0f, 0.0f, 1.0f };
    Vec4f Renderer::Color::Orange = { 1.0f, 0.6f, 0.2f, 1.0f };        
}
