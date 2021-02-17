package com.company;

public class FinalMove
{
    private int row;
    private int col;

    public FinalMove(){}
    public FinalMove(int row, int col){
        this.row = row;
        this.col = col;
    }
    public int getRow() { return row; }
    public int getCol() { return col; }
    public void setRow(int newRow) { row = newRow; }
    public void setCol(int newCol) { col = newCol; }
};