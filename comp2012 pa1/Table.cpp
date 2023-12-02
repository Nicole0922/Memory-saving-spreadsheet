#include "Table.h"

// Task 9
Table::Table()
{
    totalColumns = 0;
    columnHead = nullptr;
}

// Task 10
Table::~Table()
{
    Column* temp = nullptr;
    Column* save = this->columnHead;
    for (int i=0; i<totalColumns; i++){
        temp = save;
        save = temp->next; 
        delete temp;
        temp = nullptr;
    }
}

// Task 11
Column* Table::findColumn(int colNum) const
{
    if (colNum > totalColumns) return nullptr;
    else{
        int count = 0;
        Column* go = this->columnHead;
        for (int i=0; i<=colNum; i++){
            if (count == colNum) return go;
            else{
                go = go->next;
                count++;
            }
        }
    } 
    return nullptr;
}

// Task 12
void Table::copyInsertColumn(int fromColNum, int toColNum)
{
    // copy column non exist!, so just copy empty column to target position
    if (totalColumns > 0){
        if (fromColNum >= totalColumns){
            if (toColNum >= totalColumns){
                return;
            }
            Column* temp = new Column;

            if (toColNum == 0){
                temp->prev = nullptr;
                temp->next = this->columnHead;
                this->columnHead->prev = temp;
                this->columnHead = temp;
            }
            // zip yiap hui
            else if (toColNum < totalColumns){  // Go to here for copyInsertColumn(1000, 4)
                temp->next = findColumn(toColNum);
                temp->prev = findColumn(toColNum-1);
                findColumn(toColNum-1)->next = temp;
                findColumn(toColNum+1)->prev = temp;
            }
            totalColumns++;
        }
        // copy column exist!
        else if (fromColNum < totalColumns){
            if (findColumn(fromColNum)->getRowHead() != nullptr){
                
                // Column* temp = new Column(*findColumn(fromColNum));
                if (toColNum >= totalColumns){
                    Column* hi = nullptr;

                    // add empty columns
                    for (int i=totalColumns; i<=toColNum; i++){ //totalColumns = 5, toColNum=6
                        if (i == toColNum) hi = new Column(*findColumn(fromColNum));
                        else hi = new Column;

                        hi->prev = findColumn(i-1);
                        hi->next = nullptr;
                        findColumn(i-1)->next = hi;

                        totalColumns++;
                    }
                    return;
                }

                Column* temp = new Column(*findColumn(fromColNum));
                if (toColNum == 0){
                    temp->prev = nullptr;
                    temp->next = this->columnHead;
                    this->columnHead->prev = temp;
                    this->columnHead = temp;

                    totalColumns++;
                }
                else if (toColNum < totalColumns){
                    temp->next = findColumn(toColNum);
                    temp->prev = findColumn(toColNum-1);
                    findColumn(toColNum-1)->next = temp;
                    findColumn(toColNum+1)->prev = temp;

                    totalColumns++;
                }
            }
            else{ // fromColNum -> row head is nullptr, so nth in this column
                if(toColNum >= totalColumns){
                    return;
                }
                if (toColNum < totalColumns){
                    Column* hi = new Column;

                    if (toColNum == 0){   //copyInsertColumn(2, 0)
                        hi->prev = nullptr;
                        hi->next = this->columnHead;
                        this->columnHead->prev = hi;
                        this->columnHead = hi;
                        // cout<<"this is column 1 value "<< this->columnHead->next->getRowHead()->value <<endl;

                        totalColumns++;
                    }
                    else if (toColNum < totalColumns){ // GO TO THIs FOR copyInsertColumn(3, 1)
                        hi->prev = findColumn(toColNum-1);
                        hi->next = findColumn(toColNum);
                        findColumn(toColNum-1)->next = hi;
                        findColumn(toColNum+1)->prev = hi;

                        // cout<<"this is copyInsertColumn(3, 1) column 1 value "<< temp->getRowHead()->value <<endl;

                        totalColumns++;
                    }
                }
            }
        }
    }
    // printTable();
}

// Task 13
void Table::deleteColumn(int colNum)
{
    if (colNum < this->totalColumns){
        Column* temp = findColumn(colNum);
        Column* save = nullptr;
        temp->clearAllCells();

        if (colNum == this->totalColumns-1){

            for (int i=totalColumns-1; i>=0; i--){
                if (temp == this->columnHead){ //current column is the last column in the table
                    delete temp;
                    columnHead = nullptr;
                    totalColumns--;
                    break;
                }
                else{
                    if (temp->prev->getRowHead() == nullptr){
                        save = temp;
                        temp = temp->prev;
                        temp->next = nullptr;
                        delete save;
                        save = nullptr;
                        totalColumns--;
                    }
                    else if (temp->prev->getRowHead() != nullptr){
                        temp->prev->next = nullptr;
                        delete temp;
                        temp = nullptr;
                        totalColumns--;
                        break;
                    }
                }
            }
        }
        else if (colNum == 0){      
            findColumn(1)->prev = nullptr;
            this->columnHead = findColumn(1);
            delete temp;
            temp = nullptr;
            totalColumns--;
        }
        else if (colNum < this->totalColumns-1){
            temp->prev->next = temp->next;
            temp->next->prev = temp->prev;
            delete temp;
            temp = nullptr;
            totalColumns--;
        }
    }
}

// Task 14
Cell *Table::findCell(int colNum, int rowNum) const
{   
    Column* temp1 = findColumn(colNum);
    Cell* temp2 = temp1->findCell(rowNum);
    return temp2;
}

// Task 15
void Table::modifyCell(int colNum, int rowNum, const string &value)
{
    if (totalColumns == 0){
        this->columnHead = new Column;
        this->columnHead->next = nullptr;
        this->columnHead->prev = nullptr;
        totalColumns++;
    }
    Column* go = this->columnHead;
    Column* save = nullptr;
    for (int i=0; i<=colNum; i++){
        if (findColumn(i) == nullptr){  // the pointer now pointing to dont have memory
            go = new Column;
            if(i == colNum){   // check if the space we are now inside is the one we want to change the value
                go->modifyCell(rowNum, value);
            }

            // prev and next
            go->prev = save;
            save->next = go;
            go->next = nullptr;

            totalColumns++;
        }
        else{  //the pointer now pointing to have memory already
            if(i == colNum){
                go->modifyCell(rowNum, value);
            }
        }
        save = go;
        go = findColumn(i+1);
    }
    // printTable();
}

// Task 16
void Table::clearCell(int colNum, int rowNum)  //clearCell(8, 2)
{
    if (colNum < totalColumns){
        Column* temp = findColumn(colNum); // this is now column 8
        Column* save = nullptr;
        temp->clearCell(rowNum);
        // cout<<"this is clearCell(1, 2) column 1 value "<< temp->getRowHead()->value <<endl;
        // printTable();

        if (colNum == totalColumns-1){
            if (temp->getRowHead() == nullptr){
                // cout << "ok" << endl;
                for (int i=colNum; i>=0; i--){   //for colNum=8 
                    if (temp == this->columnHead){ //current column is the last column in the table
                        delete temp;
                        columnHead = nullptr;
                        totalColumns--;
                        break;
                    }
                    else{
                        if (temp->prev->getRowHead() == nullptr){  //need to delete this column
                            save = temp;
                            temp = temp->prev;
                            temp->next = nullptr;
                            delete save;
                            save = nullptr;
                            totalColumns--;
                            continue;
                        }
                        else if (temp->prev->getRowHead() != nullptr){  // DONT delete this column
                            Column* previousColumn = temp->prev;
                            previousColumn->next = nullptr;
                            delete temp;
                            temp = nullptr;
                            totalColumns--;
                            break;
                        }

   
                    }
                }
            }
        }
    }
    // printTable();
}

// ---------------------- provided functions: DO NOT MODIFY --------------------------
void Table::printTable() const
{

    // find the max number of rows
    int maxRows = 0;
    Column *currCol = columnHead;
    while (currCol != nullptr)
    {
        if (currCol->getTotalRows() > maxRows)
        {
            maxRows = currCol->getTotalRows();
        }
        currCol = currCol->next;
    }

    cout << "totalColumns: " << totalColumns << "\t ";
    cout << "maxRows: " << maxRows << endl;


    // string styles
    string line(12, '-');
    string doubleline(12, '=');
    string space(12, ' ');
    string headerline((totalColumns+1)*12, '=');


    // print table table header
    cout << headerline << endl;
    cout << " " << std::setw(10) << "" << "|";
    for (int i = 0; i < totalColumns; ++i)
    {
        cout<< "|" << std::setw(10) << "column "+to_string(i)+ " " << "|";
    }
    cout << endl;
    cout << headerline << endl;
    

    // print table body (row by row)
    string hline;
    for (int i = 0; i < maxRows; ++i)
    {
        hline = doubleline;    
        cout<< " " << std::setw(10) << "row "+to_string(i) + "  "<< " ";


        currCol = columnHead;

        while (currCol != nullptr)
        {
            Cell *currCell = currCol->findCell(i);
            if (currCell == nullptr)
            {
                hline += space;
                cout << " "<< std::setw(10) <<"" << " ";
            }
            else
            {
                hline += line;
                cout << "|" << std::setw(10) << currCell->value << "|";
            }
            currCol = currCol->next;
        }
        cout << endl;

        cout << hline << endl;
    }

    cout << endl;
    return;

}
