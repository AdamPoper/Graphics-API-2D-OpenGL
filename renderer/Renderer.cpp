#include "AP2DGL/Renderer.h"
namespace ap {

    uint32_t Renderer::s_referenceCounter = 0;
    Renderer::Renderer(const Window* win)
        : m_renderTarget(win), m_camera(nullptr)
    {       
        s_referenceCounter++;
        assert(s_referenceCounter < 2); // there can only be one renderer        
        m_projection = glm::ortho(0.0f, m_renderTarget->Width(), m_renderTarget->Height(), 0.0f, -1.0f, 1.0f);
        m_view = glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, 0.0f, 0.0f));
        m_vertexArray.push<float>(2); // positions
        m_vertexArray.push<float>(4); // color including alpha    
        m_vertexArray.push<float>(2); // texture coordinates
        m_vertexArray.push<float>(1); // texture slot
        m_vertexArray.push<float>(1); // yes or no has texture
        m_vertexBuffer  = new VertexBuffer();
        m_indexBuffer   = new IndexBuffer();   
        m_shaderProgram = new ShaderProgram("AP2DGL/assets/shaders/ShaderVertex.shader", "AP2DGL/assets/shaders/ShaderFragment.shader");        
        m_vertexArray.Enable();        
        Blend();
        int samplers[32] = { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 26, 27, 28, 29, 30, 31 };
        m_shaderProgram->setUniform1iv(samplers, 32, "u_Texture");
        glClearColor(0.1f, 0.1f, 0.1f, 1.0f);      
        glEnable(GL_MULTISAMPLE);  // make sure MSAA is enabled
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
       m_entities.push_back(ent);       
    }  
    void Renderer::PrepareForRender()
    {
        m_projection = glm::ortho(0.0f, m_renderTarget->Width(), m_renderTarget->Height(), 0.0f, -1.0f, 1.0f);
        glViewport(0.0f, 0.0f, m_renderTarget->Width(), m_renderTarget->Height());
        m_vertexBuffer->clearVertexBuffer();
        m_indexBuffer->clearIndexBuffer();
        if (m_camera != nullptr)
        {
            m_camera->OnUpdate();
            m_view = m_camera->GetTransform();
        }
        m_MVP = m_projection * m_view;
        m_shaderProgram->addMatrix4fv(m_MVP, "u_MVP");
    }
    void Renderer::ClearRenderBuffer()
    {
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    }
    void Renderer::onUpdate()
    {                    
        PrepareForRender();
        for (auto& e : m_entities)
        {                 
            e->setData();
            m_vertexBuffer->addVertexData(e->getData(), e->getNumVerticies());
            m_indexBuffer->updateIndicies(e->getNumIndicies());    
            if (e->hasTexture())  // only bind texture if the entity has one
                e->getTexture()->Bind((uint32_t)e->getTextureIndex());                                                                  
        }         
        m_vertexBuffer->setDynamicGeometry();       
        glDrawElements(GL_TRIANGLES, m_indexBuffer->Count(), GL_UNSIGNED_INT, nullptr);
        for (auto& e : m_entities)
        {
            glLineWidth(e->m_outlineSize);
            Draw(e->m_outlineBuffer, e->getNumVerticies(), PRIMITIVES::LINE_LOOP);
        }
        m_entities.clear();            
        m_vertexBuffer->clearVertexBuffer();         
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
        glClearColor(color.r, color.g, color.b, 1.0f);
    }
    glm::mat4 Renderer::GetCurrentMVP() const
    {
        return m_MVP;
    }
    void Renderer::DrawQuad(const Vec2f& pos, const Vec2f& size, const Vec4f& color)
    {
        Quad quad(pos, size, color);
        quad.setData();
        PrepareForRender();
        m_vertexBuffer->addVertexData(quad.getData(), quad.getNumVerticies());
        m_indexBuffer->updateIndicies(quad.getNumIndicies());
        m_vertexBuffer->setDynamicGeometry();
        m_vertexBuffer->Bind();
        m_indexBuffer->Bind();
        glDrawElements(GL_TRIANGLES, m_indexBuffer->Count(), GL_UNSIGNED_INT, nullptr);
    }
    void Renderer::DrawQuad(const Vec2f& pos, const Vec2f& size, const Vec4f& color, float degreesRotation)
    {
        Quad quad(pos, size, color);
        quad.rotate(degreesRotation);
        quad.setData();
        PrepareForRender();
        m_vertexBuffer->addVertexData(quad.getData(), quad.getNumVerticies());
        m_indexBuffer->updateIndicies(quad.getNumIndicies());
        m_vertexBuffer->setDynamicGeometry();
        m_vertexBuffer->Bind();
        m_indexBuffer->Bind();
        glDrawElements(GL_TRIANGLES, m_indexBuffer->Count(), GL_UNSIGNED_INT, nullptr);
    }
    void Renderer::DrawQuad(const Vec2f& pos, const Vec2f& size, Texture* tex)
    {
        Quad quad(pos, size, tex);
        quad.setData();
        if(quad.hasTexture())
            quad.getTexture()->Bind((uint32_t)quad.getTextureIndex());
        PrepareForRender();
        m_vertexBuffer->addVertexData(quad.getData(), quad.getNumVerticies());
        m_indexBuffer->updateIndicies(quad.getNumIndicies());
        m_vertexBuffer->setDynamicGeometry();
        m_vertexBuffer->Bind();
        m_indexBuffer->Bind();
        glDrawElements(GL_TRIANGLES, m_indexBuffer->Count(), GL_UNSIGNED_INT, nullptr);
    }
    void Renderer::DrawQuad(const Vec2f& pos, const Vec2f& size, Texture* tex, float degreesRotation)
    {
        Quad quad(pos, size, tex);
        quad.rotate(degreesRotation);
        quad.setData();
        if (quad.hasTexture())
            quad.getTexture()->Bind((uint32_t)quad.getTextureIndex());
        PrepareForRender();
        m_vertexBuffer->addVertexData(quad.getData(), quad.getNumVerticies());
        m_indexBuffer->updateIndicies(quad.getNumIndicies());
        m_vertexBuffer->setDynamicGeometry();
        m_vertexBuffer->Bind();
        m_indexBuffer->Bind();
        glDrawElements(GL_TRIANGLES, m_indexBuffer->Count(), GL_UNSIGNED_INT, nullptr);
    }
    void Renderer::DrawCircle(const Vec2f& pos, float radius, const ap::Vec4f& color)
    {        
        Circle circle(pos, radius, color);
        circle.setData();
        PrepareForRender();
        m_vertexBuffer->addVertexData(circle.getData(), circle.getNumVerticies());
        m_indexBuffer->updateIndicies(circle.getNumIndicies());
        m_vertexBuffer->setDynamicGeometry();
        m_vertexBuffer->Bind();
        m_indexBuffer->Bind();
        glDrawElements(GL_TRIANGLES, m_indexBuffer->Count(), GL_UNSIGNED_INT, nullptr);
    }
    void Renderer::DrawTriangle(const Vec2f& pos, const Vec2f& size, const Vec4f& color)
    {
        ap::Triangle triangle;
        triangle.setColor(color);
        triangle.setSize(size);
        triangle.setPosition(pos);
        triangle.setData();
        PrepareForRender();
        m_vertexBuffer->addVertexData(triangle.getData(), triangle.getNumVerticies());       
        m_vertexBuffer->setDynamicGeometry();
        m_vertexBuffer->Bind();        
        glDrawArrays(GL_TRIANGLES, 0, triangle.getNumVerticies());
    }
    void Renderer::DrawTriangle(const Vec2f& pos, const Vec2f& size, const Vec4f& color, float degreesRotation)
    {
        ap::RenderEntity triangle(3);
        triangle.setColor(color);
        triangle.setPosition(pos);
        triangle.setRadius(40.0f);
        triangle.rotate(30.0f + degreesRotation);
        triangle.setData();
        PrepareForRender();
        m_vertexBuffer->addVertexData(triangle.getData(), triangle.getNumVerticies());
        m_vertexBuffer->setDynamicGeometry();
        m_vertexBuffer->Bind();
        glDrawArrays(GL_TRIANGLES, 0, triangle.getNumVerticies());
    }
    void Renderer::Draw(const Vertex* verticies, size_t count, uint32_t primitive)
    {        
        PrepareForRender();
        m_vertexBuffer->clearVertexBuffer();
        m_vertexBuffer->addVertexData(verticies, count);
        m_vertexBuffer->setDynamicGeometry();
        m_vertexBuffer->Bind();
        glDrawArrays(primitive, 0, m_vertexBuffer->Count());
    }    
    int Renderer::ScreenShot(const char* filename)
    {
        int status = SubmitPixelReadData(filename, ap::Vec2f(0.0f, 0.0f),
            ap::Vec2f(m_renderTarget->Width(),
                m_renderTarget->Height()),
            GL_RGB, 3, IMAGE_TYPE::PNG
        );
        return status;
    }
    int Renderer::ScreenShot(const char* filename, const ap::Vec2f& start, const ap::Vec2f& dimensions)
    {
        int status = SubmitPixelReadData(filename, start, dimensions, GL_RGB, 3, IMAGE_TYPE::PNG);
        return status;
    }
    int Renderer::ScreenShot(const char* filename, const ap::Vec2f& start, const ap::Vec2f& dimensions, GLenum format, IMAGE_TYPE type)
    {
        switch (format)
        {
            case GL_BGR:
            case GL_RGB:
            {
                int status = 0;
                if(type == IMAGE_TYPE::PNG)
                    status = SubmitPixelReadData(filename, start, dimensions, format, 3, IMAGE_TYPE::PNG);
                else if(type == IMAGE_TYPE::JPG)
                    status = SubmitPixelReadData(filename, start, dimensions, format, 3, IMAGE_TYPE::JPG);
                return status;
            }            
            case GL_RGBA:
            case GL_BGRA:
            {
                int status = 0;
                if(type == IMAGE_TYPE::PNG)
                    status = SubmitPixelReadData(filename, start, dimensions, format, 4, IMAGE_TYPE::PNG);
                else if(type == IMAGE_TYPE::JPG)
                    status = SubmitPixelReadData(filename, start, dimensions, format, 4, IMAGE_TYPE::JPG);
                return status;
            }
            case GL_RED:
            case GL_GREEN:
            case GL_BLUE:
            case GL_ALPHA:
            {
                int status = 0;
                if(type == IMAGE_TYPE::PNG)
                    status = SubmitPixelReadData(filename, start, dimensions, format, 1, IMAGE_TYPE::PNG);
                else if(type == IMAGE_TYPE::JPG)
                    status = SubmitPixelReadData(filename, start, dimensions, format, 1, IMAGE_TYPE::JPG);
                return status;
            }
            default: return 0;
        }        
    }
    int Renderer::SubmitPixelReadData(const char* filename, const ap::Vec2f& start, const ap::Vec2f& dimensions, GLenum format, size_t channelCount, IMAGE_TYPE type)
    {
        uint32_t x = (uint32_t)start.x;
        uint32_t y = (uint32_t)start.y;
        uint32_t w = (uint32_t)dimensions.x;
        uint32_t h = (uint32_t)dimensions.y;
        uint8_t* pixelData = new uint8_t[channelCount * w * h];
        glPixelStorei(GL_PACK_ALIGNMENT, 1);
        glReadPixels(x, y, w, h, format, GL_UNSIGNED_BYTE, (void*)pixelData);
        stbi_flip_vertically_on_write(1);
        int success = 0;
        switch (type) {
            case IMAGE_TYPE::PNG:
            {
                success = stbi_write_png(filename, w, h, channelCount, pixelData, 0);
            }
                break;
            case IMAGE_TYPE::JPG:
            {
                success = stbi_write_jpg(filename, w, h, channelCount, pixelData, 100); // 100 for max quality
            }
                break;            
        }        
        delete[] pixelData;
        return success;
    }
    void Renderer::BindDefaultShader()
    {
        m_shaderProgram->Bind();
    }
    void Renderer::UnBindDefaultShader()
    {
        m_shaderProgram->UnBind();
    }
    ShaderProgram* Renderer::GetDefaultShader()
    {
        return m_shaderProgram;
    }
}
