
#include "Lamp.h"
#include "Random.h"

Lamp::Lamp(float posX, float posY)
{
	sprite = new Sprite("Resources/lamp.png");
	MoveTo(posX, posY);

	Generator emitter;
    emitter.imgFile = "Resources/particle.png";    // arquivo de imagem
    emitter.angle = 270.0f;                     // ângulo base do emissor
    emitter.spread = 360;                        // espalhamento em graus
    emitter.lifetime = 0.3f;                    // tempo de vida em segundos
    emitter.frequency = 0.9f;                 // tempo entre geração de novas partículas
    emitter.percentToDim = 0.3f;                // desaparece após 60% da vida
    emitter.minSpeed = 10.0f;                   // velocidade mínima das partículas
    emitter.maxSpeed = 80.0f;                  // velocidade máxima das partículas
    emitter.color.r = 1.0f;                     // componente Red da partícula 
    emitter.color.g = 0.57f;                    // componente Green da partícula 
    emitter.color.b = 0.0f;                     // componente Blue da partícula 
    emitter.color.a = 1.0f;                     // transparência da partícula

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
    RandF posY{ y - 10.0f,y + 10.0f };

    fire->Generate(posX.Rand(), posY.Rand(), 1);
    fire->Update(gameTime);
}

void Lamp::Draw()
{
	sprite->Draw(x,y,z);
    fire->Draw(Layer::FRONT, 1.0f);
}