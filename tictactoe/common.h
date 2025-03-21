#pragma once

#include <QString>
#include <iostream>
#include <stdexcept>

namespace ttt {
enum class Team : int { O, X };

inline QString ToString(const Team team) {
  return (Team::O == team) ? "O" : "X";
}

enum class Owner : int { None, O, X };

inline QString ToString(const Owner owner) {
  switch (owner) {
  case Owner::X:
    return "X";
  case Owner::O:
    return "O";
  default:
    return "";
  }
}

constexpr bool operator==(Owner owner, Team team) {
  return (owner == Owner::O && team == Team::O) ||
         (owner == Owner::X && team == Team::X);
}

constexpr bool operator!=(const Owner owner, const Team team) {
  return !(owner == team);
}

inline Owner ToOwner(const Team team) {
  return (team == Team::O) ? Owner::O : Owner::X;
}

inline Team ToTeam(const Owner owner) {
  if (owner == Owner::None) {
    throw std::invalid_argument("Cannot convert Owner::None to a Team");
  } else {
    return (owner == Owner::O) ? Team::O : Team::X;
  }
}
} // namespace ttt
