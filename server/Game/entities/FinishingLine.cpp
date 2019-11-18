

#include "FinishingLine.h"


void FinishingLine::endContact(Entity *wasTouching) {
    auto ptr = std::shared_ptr<StatusEffect>(new LapCooldown(15));
    wasTouching->addEffect(ptr);
}
