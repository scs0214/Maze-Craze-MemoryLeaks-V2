#include <iostream>
#include <stack>
#include <queue>
#include <random>
#include <ctime>
#include <unordered_map>
#include <vector>
#include <string>

const int rows = 10;
const int columns = 10;
const int directionSize = 4;
const int sublistAmount = 2;
const int startRow = 0;
const int startColumn = 0;

const double EXTRA_EDGE_PROB = 0.2;
const double POWER_SPAWN_RATE = 0.1;
const double PORTAL_SPAWN_RATE = 0.05;

enum class PowerType { NONE, DOUBLE_PLAY, CONTROL_ENEMY, JUMP_WALL };

class nodeCell {
public:
    int info;
    bool visited;
    nodeCell* next;

    nodeCell(int d, bool t) : info(d), visited(t), next(nullptr) {}
};

class Portal : public nodeCell {
private:
    std::pair<int, int> portalA, portalB;
    bool hasPortal;

public:
    Portal() : nodeCell(0, false), hasPortal(false), portalA({-1, -1}), portalB({-1, -1}) {}

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

class Power : public nodeCell {
private:
    bool powerPresence;
    PowerType powerType;
    std::pair<int, int> position; // Add position attribute

public:
    Power() : nodeCell(0, false), powerPresence(false), powerType(PowerType::NONE), position({-1, -1}) {}

    void spawnPowers() {
        std::random_device rd;
        std::mt19937 gen(rd());
        std::uniform_real_distribution<> dis(0, 1);

        for (int i = 0; i < rows; ++i) {
            for (int j = 0; j < columns; ++j) {
                if (dis(gen) < POWER_SPAWN_RATE) {
                    int type = rand() % 4; // Adjusted to include all PowerType enum values
                    powerType = static_cast<PowerType>(type);
                    position = std::make_pair(i, j); // Set the power's position
                    powerPresence = true;
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


class Treasure : public nodeCell{
private:
    std::pair<int, int> position;

public:
    Treasure() : nodeCell(-1, false), position({ -1, -1 }) {}

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

public:
    Player(const std::string& id, const std::pair<int, int>& startPos, PlayerTurn playerTurn)
        : playerID(id), currentPosition(startPos), hasWon(false), turn(playerTurn) {}

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

class nodeMatrix {
private:
    nodeCell*** matrix;
    Portal portal;
    Power power;
    Treasure treasure;  // Include treasure in nodeMatrix

    void initializeMatrix(int nodeRows, int nodeColumns) {
        matrix = new nodeCell**[nodeRows];
        for (int i = 0; i < nodeRows; ++i) {
            matrix[i] = new nodeCell*[nodeColumns];
            for (int j = 0; j < nodeColumns; ++j) {
                matrix[i][j] = new nodeCell(i * nodeColumns + j, false);
            }
        }
    }

public:
    nodeMatrix(int nodeRows, int nodeColumns) {
        initializeMatrix(nodeRows, nodeColumns);
        power.spawnPowers();
        portal.spawnPortals();
        treasure.placeTreasureEquidistant(nodeRows, nodeColumns,
                                          std::make_pair(0, 0), std::make_pair(nodeRows - 1, nodeColumns - 1));
    }

    ~nodeMatrix() {
        for (int i = 0; i < rows; ++i) {
            for (int j = 0; j < columns; ++j) {
                delete matrix[i][j];
            }
            delete[] matrix[i];
        }
        delete[] matrix;
    }

    nodeCell* getNode(int row, int column) const {
        return matrix[row][column];
    }

    // Method to move player and check if they reach the treasure
    void movePlayer(Player& player, char direction) {
    std::pair<int, int> currentPosition = player.getCurrentPosition();
    int currentRow = currentPosition.first;
    int currentCol = currentPosition.second;

    switch (direction) {
        case 'W': // Up
            if (currentRow > 0) {
                player.move(direction);
            } else {
                std::cout << "Cannot move up. Boundary reached." << std::endl;
            }
            break;
        case 'S': // Down
            if (currentRow < rows - 1) {
                player.move(direction);
            } else {
                std::cout << "Cannot move down. Boundary reached." << std::endl;
            }
            break;
        case 'A': // Left
            if (currentCol > 0) {
                player.move(direction);
            } else {
                std::cout << "Cannot move left. Boundary reached." << std::endl;
            }
            break;
        case 'D': // Right
            if (currentCol < columns - 1) {
                player.move(direction);
            } else {
                std::cout << "Cannot move right. Boundary reached." << std::endl;
            }
            break;
        default:
            std::cout << "Invalid move input." << std::endl;
            break;
    }

    // Check if player has reached the treasure after the move
    if (player.getCurrentPosition() == treasure.getPosition()) {
        player.setHasWon(true);
        std::cout << player.getPlayerID() << " has found the treasure and won!" << std::endl;
    }

    // Check if player is on a portal and teleport them if necessary
    std::pair<int, int> playerPosition = player.getCurrentPosition();
    Portal& currentPortal = getPortal();
    if (playerPosition == currentPortal.getPortalAPosition()) {
        player.setCurrentPosition(currentPortal.getPortalBPosition());
        std::cout << player.getPlayerID() << " teleported to Portal B!" << std::endl;
    } else if (playerPosition == currentPortal.getPortalBPosition()) {
        player.setCurrentPosition(currentPortal.getPortalAPosition());
        std::cout << player.getPlayerID() << " teleported to Portal A!" << std::endl;
    }

    // Check if player is on a power and apply its effect
    Power& currentPower = getPower();
    if (currentPower.isPowerPresent() && player.getCurrentPosition() == currentPower.getPosition()) {
        PowerType type = currentPower.getPowerType();
        switch (type) {
            case PowerType::DOUBLE_PLAY:
                std::cout << "DOUBLE PLAY activated!" << std::endl;
                break;
            case PowerType::CONTROL_ENEMY:
                std::cout << "CONTROL ENEMY activated!" << std::endl;
                break;
            case PowerType::JUMP_WALL:
                std::cout << "JUMP WALL activated!" << std::endl;
                break;
            case PowerType::NONE:
                // Handle case where no power is present
                std::cout << "No power present." << std::endl;
                break;
            default:
                std::cout << "Unknown power type." << std::endl;
                break;
        }
    }
}

    

    // Method to apply the effect of a power on the player
    void applyPowerEffect(Player& player, PowerType type) {
        switch (type) {
            case PowerType::DOUBLE_PLAY:
                std::cout << player.getPlayerID() << " activated DOUBLE_PLAY!" << std::endl;
                // Implement the effect of DOUBLE_PLAY (e.g., allow extra move)
                break;
            case PowerType::CONTROL_ENEMY:
                std::cout << player.getPlayerID() << " activated CONTROL_ENEMY!" << std::endl;
                // Implement the effect of CONTROL_ENEMY (e.g., control opponent's move)
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
};


int main() {
    // Initialize random seed
    std::srand(std::time(nullptr));

    // Create an instance of nodeMatrix
    nodeMatrix matrix(rows, columns);
    Portal portal;
    portal.spawnPortals();

    std::pair<int, int> positionA = portal.getPortalAPosition();
    std::pair<int, int> positionB = portal.getPortalBPosition();

    // Create players
    Player player1("Player 1", std::make_pair(0, 0), PlayerTurn::PLAYER1);
    Player player2("Player 2", std::make_pair(rows - 1, columns - 1), PlayerTurn::PLAYER2);

    // Example of accessing player information
    std::cout << "Player 1 ID: " << player1.getPlayerID() << std::endl;
    std::cout << "Player 2 ID: " << player2.getPlayerID() << std::endl;

    // Example of accessing current positions
    std::cout << "Player 1 Current Position: (" << player1.getCurrentPosition().first
              << ", " << player1.getCurrentPosition().second << ")" << std::endl;
    std::cout << "Player 2 Current Position: (" << player2.getCurrentPosition().first
              << ", " << player2.getCurrentPosition().second << ")" << std::endl;

    // Move players based on keyboard input
    char moveInput;
    while (true) {
        std::cout << "Player 1 move (WASD): ";
        std::cin >> moveInput;
        matrix.movePlayer(player1, moveInput);
        std::cout << "Player 1 Current Position: (" << player1.getCurrentPosition().first
                  << ", " << player1.getCurrentPosition().second << ")" << std::endl;

        // Check if player 1 has won
        if (player1.getHasWon()) {
            std::cout << "Game over. " << player1.getPlayerID() << " has won!" << std::endl;
            break;
        }

        std::cout << "Player 2 move (WASD): ";
        std::cin >> moveInput;
        matrix.movePlayer(player2, moveInput);
        std::cout << "Player 2 Current Position: (" << player2.getCurrentPosition().first
                  << ", " << player2.getCurrentPosition().second << ")" << std::endl;

        // Check if player 2 has won
        if (player2.getHasWon()) {
            std::cout << "Game over. " << player2.getPlayerID() << " has won!" << std::endl;
            break;
        }
    }

    return 0;
}



 

