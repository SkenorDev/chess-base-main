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
            boardIndex+=skip;
            continue;
        }
        
        placePiece(boardIndex,current);
        boardIndex++;
        }
     }
}
void Chess::placePiece(int pos, char input) {
    int player = 0;
    if (input >= 'a') {
        player = 1;
        }
     Bit *bit = new Bit();
     int tag = 0;
     switch (tolower(input)) {
        case 'p': tag = 1; break;
        case 'n': tag = 2; break;
        case 'b': tag = 3; break;
        case 'r': tag = 4; break;
        case 'q': tag = 5; break;
        case 'k': tag = 6; break;
    }

    if (player == 1)
        tag += 128;

    bit->setGameTag(tag);
     std::string spritePath;
    if(input=='b'||input=='B') spritePath = std::string("") + (player == 0 ? "w_" : "b_") + "bishop.png";
    if(input=='p'||input=='P') spritePath = std::string("") + (player == 0 ? "w_" : "b_") + "pawn.png";
    if(input=='r'||input=='R') spritePath = std::string("") + (player == 0 ? "w_" : "b_") + "rook.png";
     if(input=='n'||input=='N') spritePath = std::string("") + (player == 0 ? "w_" : "b_") + "knight.png";
    if(input=='q'||input=='Q') spritePath = std::string("") + (player == 0 ? "w_" : "b_") + "queen.png";
    if(input=='k'||input=='K') spritePath = std::string("") + (player == 0 ? "w_" : "b_") + "king.png";
    bit->LoadTextureFromFile(spritePath.c_str());
    bit->setPosition(_grid->getSquare(pos%8,pos/8)->getPosition());
    bit->setOwner(getPlayerAt(player));
    bit->setSize(pieceSize, pieceSize);
    // printf("%d",bit->getEntityType());
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
    int tag = bit.gameTag();
    int pieceType = tag & 0x7F;
    
     return true;
}

bool Chess::canBitMoveFromTo(Bit &bit, BitHolder &src, BitHolder &dst)
{
    ChessSquare* srcxy = static_cast<ChessSquare*>(&src);
    ChessSquare* dstxy = static_cast<ChessSquare*>(&dst);
     int srcx = srcxy->getColumn();
    int srcy = srcxy->getRow();
         int dstx =dstxy->getColumn();
    int dsty = dstxy->getRow();
    int player = getCurrentPlayer()->playerNumber();
    //White pawn
    if(bit.gameTag()==1&&player==0){
        printf("%d %d \n",dstx, dsty);
        if (dstx==srcx){
             if (srcy==6&&dsty==4&& getHolderAt(srcx,srcy-2).bit()==NULL){
                return true;
            }
            if (srcy-1==dsty&& getHolderAt(srcx,srcy-1).bit()==NULL){
                return true;
            }      
    }
             if (dstx == srcx - 1 && srcx != 0) {
        Bit* target = getHolderAt(dstx, dsty).bit();
        if (target != NULL && target->gameTag() > 8) { 
            return true;
        }
            }
            if (dstx == srcx + 1 && srcx != 7) {
        Bit* target = getHolderAt(dstx, dsty).bit();
        if (target != NULL && target->gameTag() > 8) {
            return true;
        }
    }
    }
    //Black Pawn
    if(bit.gameTag()==129&&player==1){
        if (dstx==srcx){
             if (srcy==1&&dsty==3&& getHolderAt(srcx,srcy+2).bit()==NULL){
                return true;
            }
            if (srcy+1==dsty&& getHolderAt(srcx,srcy+1).bit()==NULL){
                return true;
            }      
    }
           if (dstx == srcx - 1 && srcx != 0) {
        Bit* target = getHolderAt(dstx, dsty).bit();
        if (target != NULL && target->gameTag() < 8) { 
            return true;
        }
            }
            if (dstx == srcx + 1 && srcx != 7) {
        Bit* target = getHolderAt(dstx, dsty).bit();
        if (target != NULL && target->gameTag() < 8) {
            return true;
        }
    }
            
    }
    //White Knight
    if(bit.gameTag()==2&&player==0){
        Bit* target = getHolderAt(dstx, dsty).bit();
        if (target != NULL && target->gameTag() < 9) {
            return false;
        }
    if(srcx + 1 == dstx && srcy + 2 == dsty) return true;
if(srcx - 1 == dstx && srcy + 2 == dsty) return true;
if(srcx + 2 == dstx && srcy + 1 == dsty) return true;
if(srcx + 2 == dstx && srcy - 1 == dsty) return true;
if(srcx - 2 == dstx && srcy + 1 == dsty) return true;
if(srcx - 2 == dstx && srcy - 1 == dsty) return true;
if(srcx + 1 == dstx && srcy - 2 == dsty) return true;
if(srcx - 1 == dstx && srcy - 2 == dsty) return true;
    }
      //Black Knight
    if(bit.gameTag()==130&&player==1){
        Bit* target = getHolderAt(dstx, dsty).bit();
        if (target != NULL && target->gameTag() > 9) {
            return false;
        }
if(srcx + 1 == dstx && srcy + 2 == dsty) return true;
if(srcx - 1 == dstx && srcy + 2 == dsty) return true;
if(srcx + 2 == dstx && srcy + 1 == dsty) return true;
if(srcx + 2 == dstx && srcy - 1 == dsty) return true;
if(srcx - 2 == dstx && srcy + 1 == dsty) return true;
if(srcx - 2 == dstx && srcy - 1 == dsty) return true;
if(srcx + 1 == dstx && srcy - 2 == dsty) return true;
if(srcx - 1 == dstx && srcy - 2 == dsty) return true;
    }
    if(bit.gameTag()==6&&player==0){
                Bit* target = getHolderAt(dstx, dsty).bit();
        if (target != NULL && target->gameTag() < 9) {
            return false;
        }
        if(srcx+1==dstx) return true;
         if(srcx-1==dstx) return true;
          if(srcy+1==dsty) return true;
           if(srcy-1==dsty) return true;
            if(srcx+1==dstx&&srcy+1==dsty) return true;
             if(srcx+1==dstx&&srcy-1==dsty) return true;
            if(srcx-1==dstx&&srcy+1==dsty) return true;
             if(srcx-1==dstx&&srcy-1==dsty) return true;
    }
        if(bit.gameTag()==134&&player==1){
                Bit* target = getHolderAt(dstx, dsty).bit();
        if (target != NULL && target->gameTag() > 9) {
            return false;
        }
                if(srcx+1==dstx) return true;
         if(srcx-1==dstx) return true;
          if(srcy+1==dsty) return true;
           if(srcy-1==dsty) return true;
            if(srcx+1==dstx&&srcy+1==dsty) return true;
             if(srcx+1==dstx&&srcy-1==dsty) return true;
            if(srcx-1==dstx&&srcy+1==dsty) return true;
             if(srcx-1==dstx&&srcy-1==dsty) return true;
    }
    return false;
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
