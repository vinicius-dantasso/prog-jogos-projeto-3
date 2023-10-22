
#include "Lamp.h"
#include "Random.h"

Lamp::Lamp(float posX, float posY)
{
	sprite = new Sprite("Resources/lamp.png");
	MoveTo(posX, posY);

	Generator emitter;
    emitter.imgFile = "Resources/particle.png";    // arquivo de imagem
    emitter.angle = 270.0f;                     // �ngulo base do emissor
    emitter.spread = 360;                        // espalhamento em graus
    emitter.lifetime = 0.3f;                    // tempo de vida em segundos
    emitter.frequency = 0.9f;                 // tempo entre gera��o de novas part�culas
    emitter.percentToDim = 0.3f;                // desaparece ap�s 60% da vida
    emitter.minSpeed = 10.0f;                   // velocidade m�nima das part�culas
    emitter.maxSpeed = 80.0f;                  // velocidade m�xima das part�culas
    emitter.color.r = 1.0f;                     // componente Red da part�cula 
    emitter.color.g = 0.57f;                    // componente Green da part�cula 
    emitter.color.b = 0.0f;                     // componente Blue da part�cula 
    emitter.color.a = 1.0f;                     // transpar�ncia da part�cula

    fire = new Particles(emitter);
}

Lamp::~Lamp()
{
	delete sprite;
    delete fire;
}

void Lamp::Update()
{
    RandF posX{ x - 10.0f, x + 10.0f };
    RandF posY{ y - 10.0f, y + 10.0f };

    fire->Generate(posX.Rand(), posY.Rand(), 1);
    fire->Update(gameTime);
}

void Lamp::Draw()
{
	sprite->Draw(x,y,z);
    fire->Draw(Layer::FRONT, 1.0f);
}