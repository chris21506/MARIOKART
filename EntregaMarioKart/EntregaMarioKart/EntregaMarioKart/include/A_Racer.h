#pragma once

#include "ECS/Actor.h"
#include <SFML/System/Vector2.hpp>
#include <SFML/Graphics/Rect.hpp>
#include <vector>
#include <string>

/**
 * @class A_Racer
 * @brief Corredor (NPC/Jugador) que sigue un path, cuenta vueltas y soporta
 *        un offset de �ngulo para alinear el sprite con la direcci�n de marcha.
 */
class A_Racer : public Actor {
public:
  /**
   * @brief Construye un corredor.
   * @param name Nombre del actor (para GUI/depuraci�n).
   * @param playerId Identificador opcional del jugador (0 = IA).
   */
  explicit A_Racer(const std::string& name, int playerId = 0);

  /**
   * @brief Hook de inicio (no usado actualmente).
   */
  void start() override {}

  /**
   * @brief Actualiza el corredor: steering hacia el siguiente waypoint,
   *        avance de vueltas y orientaci�n del sprite.
   * @param deltaTime Tiempo transcurrido desde el frame anterior.
   */
  void update(float deltaTime) override;

  /**
   * @brief Define la ruta (lista de waypoints en orden) que seguir� el corredor.
   * @param pathPoints Polil�nea cerrada (o abierta) de puntos en coordenadas de mundo.
   */
  void setPath(const std::vector<sf::Vector2f>& pathPoints);

  /**
   * @brief Reinicia el estado del corredor al inicio del path (sin vueltas ni podio).
   */
  void reset();

  /**
   * @brief Define el rect�ngulo de meta utilizado para contar vueltas.
   * @param rect Rect�ngulo en coordenadas de mundo.
   */
  void setFinishLine(const sf::FloatRect& rect) { m_finishLine = rect; }

  /**
   * @brief Fija el n�mero total de vueltas.
   * @param laps Conteo de vueltas a completar.
   */
  void setTotalLaps(int laps) { m_totalLaps = laps; }

  /**
   * @brief Obtiene la vuelta actual (0..totalLaps).
   */
  int  getCurrentLap() const { return m_currentLap; }

  /**
   * @brief Devuelve el total de vueltas configurado.
   */
  int  getTotalLaps()  const { return m_totalLaps; }

  /**
   * @brief Indica si ya termin� todas las vueltas.
   */
  bool isFinished()    const { return m_currentLap >= m_totalLaps; }

  /**
   * @brief Ajusta la velocidad m�xima del corredor (px/s).
   * @param s Nueva velocidad m�xima.
   */
  void  setMaxSpeed(float s) { m_maxSpeed = s; }

  /**
   * @brief Devuelve la velocidad m�xima actual (px/s).
   */
  float getMaxSpeed() const { return m_maxSpeed; }

  /**
   * @brief Posici�n de podio alcanzada (0 = a�n corriendo, 1..N = finalizado).
   */
  int   getPlace() const { return m_place; }

  /**
   * @brief Fija la posici�n de podio alcanzada.
   * @param p 1..N cuando finaliza; 0 para �corriendo�.
   */
  void  setPlace(int p) { m_place = p; }

  /**
   * @brief Progreso normalizado a lo largo del loop actual [0..1].
   */
  float getProgress() const;

  /**
   * @brief Define un offset angular (en grados) que se suma a la orientaci�n
   *        calculada por el steering para alinear el sprite.
   *        �til cuando la textura �mira hacia arriba� o �a la derecha�.
   * @param deg Offset en grados (p. ej., -90 si el sprite mira hacia arriba).
   */
  void  setSpriteAngleOffset(float deg) { m_spriteAngleOffset = deg; }

  /**
   * @brief Obtiene el offset angular aplicado al sprite (en grados).
   */
  float getSpriteAngleOffset() const { return m_spriteAngleOffset; }

private:
  /**
   * @brief L�gica de seguimiento del path (Pure Pursuit + arrive).
   * @param deltaTime Tiempo transcurrido desde el frame anterior.
   */
  void doPathFollowing(float deltaTime);

  // --- Ruta / waypoints ---
  std::vector<sf::Vector2f> path;   ///< Waypoints del recorrido, en orden.
  int   currentWaypointIndex = 0;   ///< �ndice del waypoint objetivo actual.

  // --- Par�metros de steering ---
  float lookaheadDistance = 60.f;   ///< Distancia de mirada hacia delante (suaviza curvas).
  float arriveRadius = 30.f;   ///< Umbral para �cambiar� al siguiente waypoint.
  float m_maxSpeed = 160.f;  ///< Velocidad m�xima (px/s).

  // --- Meta / vueltas ---
  sf::FloatRect m_finishLine{};     ///< Rect�ngulo usado para detectar paso por meta.
  int  m_currentLap = 0;            ///< Vuelta actual.
  int  m_totalLaps = 3;            ///< Vueltas a completar.
  bool m_crossedLastFrame = false;  ///< Evita contar varias veces la misma pasada por meta.

  // --- Estado de carrera ---
  int  m_place = 0;                 ///< 0 = corriendo; 1..N = posici�n final.
  int  m_playerIndex = 0;           ///< Identificador opcional para GUI/depuraci�n.

  // --- Orientaci�n del sprite ---
  float m_spriteAngleOffset = -90.f; ///< Offset en grados sumado a la rotaci�n calculada.
};
