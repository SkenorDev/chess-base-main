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