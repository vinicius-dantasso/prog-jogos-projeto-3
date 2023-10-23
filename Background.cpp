/**********************************************************************************
// Background (Código Fonte)
// 
// Criação:     07 Dez 2011
// Atualização: 01 Nov 2021
// Compilador:  Visual C++ 2019
//
// Descrição:   Representa um pano de fundo maior que a janela
//
**********************************************************************************/


#include "Background.h"
#include "Engine.h"

// -------------------------------------------------------------------------------

Background::Background(string filename1, string filename2, string filename3)
{
    // carrega imagem
    image = new Image(filename1);

    // configura registro spriteData
    spriteData1.x = Engine::window->CenterX();
    spriteData1.y = Engine::window->CenterY();
    spriteData1.depth = Layer::BACK;
    spriteData1.scale = 1.0f;    
    spriteData1.rotation = 0.0f;
    spriteData1.color = Color(1, 1, 1, 1);
    spriteData1.texture = image->View();

    // carrega imagem
    image = new Image(filename2);

    // configura registro spriteData
    spriteData2.x = Engine::window->CenterX();
    spriteData2.y = Engine::window->CenterY();
    spriteData2.depth = Layer::BACK;
    spriteData2.scale = 1.0f;
    spriteData2.rotation = 0.0f;
    spriteData2.color = Color(1, 1, 1, 1);
    spriteData2.texture = image->View();

    // carrega imagem
    image = new Image(filename3);

    // configura registro spriteData
    spriteData3.x = Engine::window->CenterX();
    spriteData3.y = Engine::window->CenterY();
    spriteData3.depth = Layer::BACK;
    spriteData3.scale = 1.0f;
    spriteData3.rotation = 0.0f;
    spriteData3.color = Color(1, 1, 1, 1);
    spriteData3.texture = image->View();
}

// -------------------------------------------------------------------------------

Background::~Background()
{
    delete image;
}

// -------------------------------------------------------------------------------

void Background::Draw(ViewPort & vp)
{ 
    // define um sprite com a região do pano de fundo limitada pela viewport
    spriteData1.width = uint(vp.right - vp.left);
    spriteData1.height = uint(vp.bottom - vp.top);
    spriteData1.texCoord.x = vp.left / float(image->Width());
    spriteData1.texCoord.y = vp.top / float(image->Height());
    spriteData1.texSize.x = spriteData1.width / float(image->Width());
    spriteData1.texSize.y = spriteData1.height / float(image->Height());

    // define um sprite com a região do pano de fundo limitada pela viewport
    spriteData2.width = uint(vp.right - vp.left);
    spriteData2.height = uint(vp.bottom - vp.top);
    spriteData2.texCoord.x = vp.left / float(image->Width());
    spriteData2.texCoord.y = vp.top / float(image->Height());
    spriteData2.texSize.x = spriteData2.width / float(image->Width());
    spriteData2.texSize.y = spriteData2.height / float(image->Height());

    // define um sprite com a região do pano de fundo limitada pela viewport
    spriteData3.width = uint(vp.right - vp.left);
    spriteData3.height = uint(vp.bottom - vp.top);
    spriteData3.texCoord.x = vp.left / float(image->Width());
    spriteData3.texCoord.y = vp.top / float(image->Height());
    spriteData3.texSize.x = spriteData3.width / float(image->Width());
    spriteData3.texSize.y = spriteData3.height / float(image->Height());

    // adiciona o sprite na lista de desenho
    Engine::renderer->Draw(spriteData1);
    Engine::renderer->Draw(spriteData2);
    Engine::renderer->Draw(spriteData3);
}

// -------------------------------------------------------------------------------

