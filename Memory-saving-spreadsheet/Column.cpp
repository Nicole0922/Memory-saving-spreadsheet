#include "Column.h"

// Task 1
Column::Column()
{
    totalRows = 0;
    rowHead = nullptr;
    next = nullptr;
    prev = nullptr;
}

// Task 2
Column::Column(Column *prev)
{
    totalRows = 0;
    rowHead = nullptr;
    this->next = nullptr;
    this->prev = prev;
}

// Task 3
Column::Column(const Column &c)
{
    this->totalRows = c.totalRows;
    this->next = nullptr;
    this->prev = nullptr;

    if (c.rowHead == nullptr) this->rowHead = nullptr;
    else{
        this->rowHead = new Cell;
        this->rowHead->next = c.rowHead->next;
        this->rowHead->prev = nullptr;
        this->rowHead->value = c.rowHead->value;

        Cell* temp = this->rowHead;
        Cell* copy = c.rowHead;
        Cell* save = nullptr;

        for (int i=0; i<c.totalRows; i++){
            if (temp != this->rowHead){
                temp = new Cell;
                temp->next = nullptr;
                temp->prev = copy->prev;
                temp->value = copy->value;
                save->next = temp;
            }
            save = temp;
            temp = temp->next;
            copy = copy->next;
        }
    }
}

// Task 4
Column::~Column()
{
    Cell* temp = nullptr;
    Cell* save = this->rowHead;
    for (int i=0; i<totalRows; i++){
        temp = save;  
        save = temp->next;
        delete temp;
        temp =nullptr;
    }
}

// Task 5
Cell *Column::findCell(int rowNum)
{    
    if (rowNum > totalRows) return nullptr;
    else{
        Cell* go = this->rowHead;
        for (int i=0; i<=rowNum; i++){
            if (i == rowNum) return go;
            else{
                go = go->next;
            }
        }
    } 
    return nullptr;
}

// Task 6
void Column::modifyCell(int rowNum, const string &value)
{
    if (totalRows == 0){
        this->rowHead = new Cell;
        this->rowHead->next = nullptr;
        this->rowHead->prev = nullptr;
        this->rowHead->value = "";
        totalRows++;
    }
    Cell* go = this->rowHead;
    Cell* save = nullptr;
    for (int i=0; i<=rowNum; i++){
        if (findCell(i) == nullptr){  // the pointer now pointing to dont have memory
            go = new Cell;

            // value
            if(i == rowNum){   // check if the space we are now inside is the one we want to change the value
                go->value = value;
            }
            else go->value = "";

            // prev and next
            go->prev = save;
            go->next = nullptr;
            save->next = go;

            totalRows++;
        }
        else{  //the pointer now pointing to have memory already
            if(i == rowNum){
                go->value = value;
            }
        }
        save = go;
        go = findCell(i+1);
    }
}

// Task 7
void Column::clearCell(int rowNum)
{
    if (rowNum < totalRows){
        Cell* temp = findCell(rowNum);
        Cell* save = nullptr;
        if (rowNum == totalRows-1){
            for (int i=totalRows-1; i>=0; i--){
                if (temp->prev == nullptr){
                    delete temp;
                    totalRows--;
                    rowHead = nullptr;
                    break;
                }
                else{
                    if (temp->prev->value == ""){
                        save = temp;
                        temp = temp->prev; 
                        delete save;
                        totalRows--;
                    }
                    else{
                        delete temp;
                        totalRows--;
                        break;
                    }
                }
            }
        }
        else if (rowNum < totalRows-1){
            temp->value = "";
        }
    }
}

// Task 8
void Column::clearAllCells()
{
    Cell* temp = findCell(totalRows-1);
    Cell* save = nullptr;
    for (int i=totalRows-1; i>=0; i--){
        save = temp;
        temp = temp->prev; 
        delete save;
        totalRows--;
    }
}

// ---------------------- provided functions: DO NOT MODIFY --------------------------
void Column::printColumn() const
{
    // string styles
    string line(12, '-');
    string doubleline(12, '=');
    string space(12, ' ');



    cout << "totalRows: " << totalRows << endl;

    // table header
    cout << doubleline + doubleline << endl;
    cout << " " << std::setw(10) << "" << " ";
    cout << "|" << std::setw(10)  << "column " << "|" <<endl;   
    cout << doubleline + doubleline << endl;

    // table body (row by row)
    Cell* current = rowHead;
    for (int i =0 ; i < totalRows; ++i){
        cout << " " << std::setw(10) << "row " + to_string(i) + " " << " " ;
        cout << "|" << std::setw(10) << current->value << "|" << endl;
        current = current->next;
        cout << doubleline + line << endl;
    }

    cout << endl;

}
