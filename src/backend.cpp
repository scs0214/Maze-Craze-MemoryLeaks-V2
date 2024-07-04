#include <iostream>
#include <random>
#include <ctime>
#include <cmath>

const int rows = 4;
const int columns = 4;
const double POWER_SPAWN_RATE = 0.1;
const double PORTAL_SPAWN_RATE = 0.05;

enum class PowerType { NONE, DOUBLE_PLAY, CONTROL_ENEMY, JUMP_WALL };

class NodeCell {
public:
    int info;
    bool visited;
    NodeCell* next;

    NodeCell(int d, bool t) : info(d), visited(t), next(nullptr) {}
};

class Portal : public NodeCell {
private:
    std::pair<int, int> portalA, portalB;
    bool hasPortal;

public:
    Portal() : NodeCell(0, false), hasPortal(false), portalA({0, 0}), portalB({0, 0}) {}

    void spawnPortals() {
        std::random_device rd;
        std::mt19937 gen(rd());
        std::uniform_real_distribution<> dis(0, 1);
        hasPortal = false;

        for (int i = 0; i < rows; ++i) {
            for (int j = 0; j < columns; ++j) {
                if (!hasPortal && dis(gen) < PORTAL_SPAWN_RATE) {
                    portalA = std::make_pair(i, j);
                    hasPortal = true;
                } else if (hasPortal && dis(gen) < PORTAL_SPAWN_RATE) {
                    portalB = std::make_pair(i, j);
                    break;
                }
            }
            if (hasPortal && portalB.first != -1 && portalB.second != -1) break;
        }
    }

    std::pair<int, int> getPortalAPosition() const {
        return portalA;
    }

    std::pair<int, int> getPortalBPosition() const {
        return portalB;
    }
};

class Power : public NodeCell {
private:
    bool powerPresence;
    PowerType powerType;
    std::pair<int, int> position;

public:
    Power() : NodeCell(0, false), powerPresence(false), powerType(PowerType::NONE), position(std::make_pair(0, 0)) {}

    Power(int r, int c) : NodeCell(0, false), powerPresence(false), powerType(PowerType::NONE), position(std::make_pair(r, c)) {}
    
    void spawnPowers() {
        std::random_device rd;
        std::mt19937 gen(rd());
        std::uniform_real_distribution<> dis(0, 1);

        for (int i = 0; i < rows; ++i) {
            for (int j = 0; j < columns; ++j) {
                if (dis(gen) < POWER_SPAWN_RATE) {
                    int type = std::rand() % 3; // Adjusted to include all PowerType enum values except NONE
                    powerType = static_cast<PowerType>(type + 1); // Ensures it maps to DOUBLE_PLAY, CONTROL_ENEMY, or JUMP_WALL
                    powerPresence = true;
                    position = std::make_pair(i, j);
                    return;
                }
            }
        }
    }

    bool isPowerPresent() const {
        return powerPresence;
    }

    PowerType getPowerType() const {
        return powerType;
    }

    std::pair<int, int> getPosition() const {
        return position;
    }
};

enum class PlayerTurn { PLAYER1, PLAYER2 };

class Player {
private:
    std::string playerID;
    std::pair<int, int> currentPosition;
    bool hasWon;
    PlayerTurn turn;
    bool hasExtraMove; // Track if the player has an extra move due to DOUBLE_PLAY

public:
    Player(const std::string& id, const std::pair<int, int>& startPos, PlayerTurn playerTurn)
        : playerID(id), currentPosition(startPos), hasWon(false), turn(playerTurn), hasExtraMove(false) {}

    std::string getPlayerID() const {
        return playerID;
    }

    std::pair<int, int> getCurrentPosition() const {
        return currentPosition;
    }

    bool getHasWon() const {
        return hasWon;
    }

    PlayerTurn getTurn() const {
        return turn;
    }

    bool getHasExtraMove() const {
        return hasExtraMove;
    }

    void setPlayerID(const std::string& id) {
        playerID = id;
    }

    void setCurrentPosition(const std::pair<int, int>& pos) {
        currentPosition = pos;
    }

    void setHasWon(bool won) {
        hasWon = won;
    }

    void setTurn(PlayerTurn playerTurn) {
        turn = playerTurn;
    }

    void setHasExtraMove(bool extraMove) {
        hasExtraMove = extraMove;
    }

    void move(char direction) {
        int currentRow = currentPosition.first;
        int currentCol = currentPosition.second;

        switch (direction) {
            case 'W': // Up
                currentPosition = std::make_pair(currentRow - 1, currentCol);
                break;
            case 'S': // Down
                currentPosition = std::make_pair(currentRow + 1, currentCol);
                break;
            case 'A': // Left
                currentPosition = std::make_pair(currentRow, currentCol - 1);
                break;
            case 'D': // Right
                currentPosition = std::make_pair(currentRow, currentCol + 1);
                break;
            default:
                std::cout << "Invalid move input." << std::endl;
                break;
        }
    }
};

class Treasure : public NodeCell {
private:
    std::pair<int, int> position;

public:
    Treasure() : NodeCell(-1, false), position({ -1, -1 }) {}

    void placeTreasureEquidistant(int rows, int columns, const std::pair<int, int>& player1Start, const std::pair<int, int>& player2Start) {
        std::random_device rd;
        std::mt19937 gen(rd());
        std::uniform_int_distribution<> disRow(0, rows - 1);
        std::uniform_int_distribution<> disCol(0, columns - 1);

        int row, col;
        do {
            row = disRow(gen);
            col = disCol(gen);

            int distanceToPlayer1 = std::abs(row - player1Start.first) + std::abs(col - player1Start.second);
            int distanceToPlayer2 = std::abs(row - player2Start.first) + std::abs(col - player2Start.second);

            if (distanceToPlayer1 == distanceToPlayer2) {
                position = { row, col };
                break;
            }

        } while (true);
    }
    
    std::pair<int, int> Treasure::getPosition() const {
        return position;
    }

};

class NodeMatrix {
private:
    NodeCell*** matrix;
    Portal portal;
    Power power;
    Treasure treasure;

    void initializeMatrix(int nodeRows, int nodeColumns) {
        matrix = new NodeCell**[nodeRows];
        int count = 0;
        for (int i = 0; i < nodeRows; ++i) {
            matrix[i] = new NodeCell*[nodeColumns];
            for (int j = 0; j < nodeColumns; ++j) {
                matrix[i][j] = new NodeCell(count, false);
                count++;
            }
        }
    }

public:
    NodeMatrix(int nodeRows, int nodeColumns) {
        initializeMatrix(nodeRows, nodeColumns);
        power.spawnPowers();
        portal.spawnPortals();
        treasure.placeTreasureEquidistant(nodeRows, nodeColumns,
        std::make_pair(0, 0), std::make_pair(nodeRows - 1, nodeColumns - 1));
    }

    
    NodeCell* getNode(int row, int column) const {
        return matrix[row][column];
    }

    void applyPowerEffect(NodeMatrix& matrix, Player& player, Player& otherPlayer, PowerType type) {
        switch (type) {
            case PowerType::DOUBLE_PLAY:
                std::cout << player.getPlayerID() << " activated DOUBLE_PLAY!" << std::endl;
                player.setHasExtraMove(true); // Allow an extra move
                break;
            case PowerType::CONTROL_ENEMY:
                std::cout << player.getPlayerID() << " activated CONTROL_ENEMY!" << std::endl;
                char moveInput;
                std::cout << player.getPlayerID() << " controls " << otherPlayer.getPlayerID() << "'s move (WASD): ";
                std::cin >> moveInput;
                player.move(moveInput);
                break;
            case PowerType::JUMP_WALL:
                std::cout << player.getPlayerID() << " activated JUMP_WALL!" << std::endl;
                // Implement the effect of JUMP_WALL (e.g., move through walls)
                break;
            default:
                std::cout << "Unknown power type." << std::endl;
                break;
        }
    }

    Power& getPower() {
        return power;
    }

    Portal& getPortal() {
        return portal;
    }

    Treasure& getTreasure() {
        return treasure;
    }
};