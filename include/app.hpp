/**
 * \file app.hpp
 * \brief App class header
 * \author João Vitor Espig (JotaEspig)
 * \date June 12, 2024
 * \version June 12, 2024
 **/
#pragma once

#include <axolote/engine.hpp>

/**
 * \brief Main class of the application
 * \author João Vitor Espig (JotaEspig)
 * \date June 12, 2024
 * \version June 12, 2024
 **/
class App : public axolote::Window {
public:
    /**
     * \brief App constructor
     * \author João Vitor Espig (JotaEspig)
     * \date June 12, 2024
     * \version June 12, 2024
     **/
    void main_loop();

private:
    /** Should use glPolygonMode as GL_FILL or GL_LINE **/
    bool is_fill = true;

    /**
     * \brief Process input
     * \author João Vitor Espig (JotaEspig)
     * \date June 12, 2024
     * \version June 12, 2024
     * \param dt - Delta time
     **/
    void process_input(float dt);
};
