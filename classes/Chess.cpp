#include "Chess.h"
#include <limits>
#include <cmath>

Chess::Chess()
{
    _grid = new Grid(8, 8);
}

Chess::~Chess()
{
    delete _grid;
}

char Chess::pieceNotation(int x, int y) const
{
    const char *wpieces = { "0PNBRQK" };
    const char *bpieces = { "0pnbrqk" };
    Bit *bit = _grid->getSquare(x, y)->bit();
    char notation = '0';
    if (bit) {
        notation = bit->gameTag() < 128 ? wpieces[bit->gameTag()] : bpieces[bit->gameTag()-128];
    }
    return notation;
}

Bit* Chess::PieceForPlayer(const int playerNumber, ChessPiece piece)
{
    const char* pieces[] = { "pawn.png", "knight.png", "bishop.png", "rook.png", "queen.png", "king.png" };

    Bit* bit = new Bit();
    // should possibly be cached from player class?
    const char* pieceName = pieces[piece - 1];
    std::string spritePath = std::string("") + (playerNumber == 0 ? "w_" : "b_") + pieceName;
    bit->LoadTextureFromFile(spritePath.c_str());
    bit->setOwner(getPlayerAt(playerNumber));
    bit->setSize(pieceSize, pieceSize);

    return bit;
}

void Chess::setUpBoard()
{
    setNumberOfPlayers(2);
    _gameOptions.rowX = 8;
    _gameOptions.rowY = 8;

    _grid->initializeChessSquares(pieceSize, "boardsquare.png");
    FENtoBoard("rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR");
    //FENtoBoard("rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w KQkq - 0 1");

    startGame();
}
   //EX: setup bishop in bottom left +1 +1
    //  Bit *bit = new Bit();
    // std::string spritePath = std::string("") + (0 == 0 ? "w_" : "b_") + "bishop.png";
    // bit->LoadTextureFromFile(spritePath.c_str());
    // bit->setPosition(_grid->getSquare(1,1)->getPosition());
    //    bit->setOwner(getPlayerAt(0));
    // bit->setSize(pieceSize, pieceSize);
    // _grid->getSquare(1,1)->setBit(bit);

    // convert a FEN string to a board
    // FEN is a space delimited string with 6 fields
    // 1: piece placement (from white's perspective)
    // NOT PART OF THIS ASSIGNMENT BUT OTHER THINGS THAT CAN BE IN A FEN STRING
    // ARE BELOW
    // 2: active color (W or B)
    // 3: castling availability (KQkq or -)
    // 4: en passant target square (in algebraic notation, or -)
    // 5: halfmove clock (number of halfmoves since the last capture or pawn advance)
    //FENtoBoard("rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR");
void Chess::FENtoBoard(const std::string& fen) {
    int boardIndex=0;
    for (int i=0;i<fen.length();i++){
        char current = fen[i];
        if(boardIndex<64){
        if(current=='/'){
            continue;
        }
        //convert into corelating int
        int skip = current-'0';
        if(skip>0&&skip<9){
             printf("%d \n",skip);
            boardIndex+=skip;
            continue;
        }
        
        placePiece(boardIndex,current);
        boardIndex++;
        }
        else{
            if(current=='B'|| current == 'b') {
                _gameOptions.currentTurnNo=1;
            }
            if(current=='W'|| current == 'w') {
                _gameOptions.currentTurnNo=0;
            }
        }
    }
}
void Chess::placePiece(int pos, char input) {
    int player = 0;
    if (input >= 'a') {
        player = 1;
        }
     Bit *bit = new Bit();
    std::string spritePath = std::string("") + (player == 0 ? "w_" : "b_") + "bishop.png";
    bit->LoadTextureFromFile(spritePath.c_str());
    bit->setPosition(_grid->getSquare(pos%8,pos/8)->getPosition());
    bit->setOwner(getPlayerAt(player));
    bit->setSize(pieceSize, pieceSize);
    _grid->getSquare(pos%8,pos/8)->setBit(bit);
}
 


bool Chess::actionForEmptyHolder(BitHolder &holder)
{
    return false;
}

bool Chess::canBitMoveFrom(Bit &bit, BitHolder &src)
{
    // need to implement friendly/unfriendly in bit so for now this hack
    int currentPlayer = getCurrentPlayer()->playerNumber() * 128;
    int pieceColor = bit.gameTag() & 128;
    if (pieceColor == currentPlayer) return true;
    return false;
}

bool Chess::canBitMoveFromTo(Bit &bit, BitHolder &src, BitHolder &dst)
{
    return true;
}

void Chess::stopGame()
{
    _grid->forEachSquare([](ChessSquare* square, int x, int y) {
        square->destroyBit();
    });
}

Player* Chess::ownerAt(int x, int y) const
{
    if (x < 0 || x >= 8 || y < 0 || y >= 8) {
        return nullptr;
    }

    auto square = _grid->getSquare(x, y);
    if (!square || !square->bit()) {
        return nullptr;
    }
    return square->bit()->getOwner();
}

Player* Chess::checkForWinner()
{
    return nullptr;
}

bool Chess::checkForDraw()
{
    return false;
}

std::string Chess::initialStateString()
{
    return stateString();
}

std::string Chess::stateString()
{
    std::string s;
    s.reserve(64);
    _grid->forEachSquare([&](ChessSquare* square, int x, int y) {
            s += pieceNotation( x, y );
        }
    );
    return s;}

void Chess::setStateString(const std::string &s)
{
    _grid->forEachSquare([&](ChessSquare* square, int x, int y) {
        int index = y * 8 + x;
        char playerNumber = s[index] - '0';
        if (playerNumber) {
            square->setBit(PieceForPlayer(playerNumber - 1, Pawn));
        } else {
            square->setBit(nullptr);
        }
    });
}
