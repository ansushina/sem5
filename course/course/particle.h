#ifndef PARTICLE_H
#define PARTICLE_H

namespace ParticlesSystems {
class Partilce {

private:
    // позиция частицы
    float position[3];
    // размер
    float _size;
    // время жизни
    float _lifeTime;
    // вектор гравитации
    float Grav[3];
    // ускорение частицы
    float power[3];
    //коэффициент затухания силы
    float attenuation;
    // набранная скорость
    float speed[3];
    // временной интервал активации частицы
    float LastTime = 0;
    // конструктор класса
public:
    Partilce( float x, float y, float z, float size, float lifeTime, float start_time):
        _size(size),
        _lifeTime(lifeTime),
        LastTime(start_time)
    {
        // записываем все начальные настройки частицы, устанавливаем начальный коэффициент затухания
        // и обнуляем скорость и силу приложенную к частице
        position[0] = x;
        position[1] = y;
        position[1] = z;
        speed[0] = 0;
        speed[1] = 0;
        speed[2] = 0;
        Grav[0] = 0;
        Grav[1] = -9.8f;
        Grav[2] = 0;
        attenuation = 3.33f;
        power[0] = 0;
        power[0] = 0;
        power[0] = 0;
    }
    // функция установки ускорения, действующего на частицу
    void SetPower( float x, float y, float z) {
        power[0] = x;
        power[1] = y;
        power[2] = z;
    }
    // инвертирование скорости частицы по заданной оси с указанным затуханием
    // удобно использовать для простой демонстрации столкновений, например, с землей
    void InvertSpeed( int os, float attenuation) {
        speed[os] *= -1 * attenuation;
    }
    // получение размера частицы
    float GetSize() {
        return _size;
    }
    // установка нового значения затухания
    void setAttenuation(float new_value) {
        attenuation = new_value;
    }
    // обновление позиции частицы
    void UpdatePosition(float timeNow) {
        // определяем разницу во времени, прошедшего с последнего обновления
        // позиции частицы (ведь таймер может быть не фиксированный)
        float dTime = timeNow - LastTime;
        _lifeTime -= dTime;
        // обновляем последнюю отметку временного интервала
        LastTime = timeNow;
        // перерасчитываем ускорение, движущее частицу, с учетом затухания
        for( int a = 0; a < 3; a++) {
            if (power[a] > 0) {
                power[a] -= attenuation * dTime;
                if (power[a] <= 0)
                    power[a] = 0;
            }
            // перерасчитываем позицию частицы с учетом гравитации, вектора ускорения и прошедший промежуток времени
            position[a] += (speed[a] * dTime + (Grav[a] + power[a]) * dTime * dTime);
            // обновляем скорость частицы
            speed[a] += (Grav[a] + power[a]) * dTime;
        }
    }
    // проверка, не вышло ли время жизни частицы
    bool isLife() {
        if (_lifeTime > 0) {
            return true ;
        } else {
            return false ;
        }
    }
    // получение координат частицы
    float GetPositionX() {
        return position[0];
    }
    float GetPositionY() {
        return position[1];
    }
    float GetPositionZ() {
        return position[2];
    }
};
}
//Подробнее на esate.ru:
//http://esate.ru/uroki/OpenGL/uroki-OpenGL-c-sharp/sistemy_chastits_opengl_2/?rv1

#endif // PARTICLE_H
