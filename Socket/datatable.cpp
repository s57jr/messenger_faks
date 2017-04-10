#include "datatable.h"



namespace client {
DataTable::DataTable(int32_t nColumns) {
    if (nColumns < 0) {
        std::cerr << "nColumns must be >= 0" << std::endl;
        exit(EXIT_FAILURE);
    }
    this->columns = nColumns;
}

DataTable::~DataTable() {
}

int32_t DataTable::getNColumns() {
    return this->columns;
}

int32_t DataTable::getNRows() {
    return this->data.size();
}

void DataTable::set(int32_t row, int32_t column, int32_t value) {
    if (column < 0 || column >= this->columns) {
        std::cerr
                << "Column index (" << std::to_string(column) << ") out of range (0.."
                        << std::to_string(this->columns) << ")." << std::endl;
        exit(1);
    }

    if (row < 0) {
        std::cerr << "Row index < 0" << std::endl;
        exit(1);
    }

    while (this->data.size() <= row) {
        std::vector<int32_t> newRow = std::vector<int32_t>(this->columns);
        for (int i = 0; i < this->columns; i++) {
            newRow[i] = 0;
        }
        this->data.push_back(newRow);
    }

    this->data[row][column] = value;
}

int32_t DataTable::get(int32_t row, int32_t column){
    if (column < 0 || column >= this->columns) {
        std::cerr << "Column index (" << std::to_string(column) << ") out of range (0.." << std::to_string(this->columns) << ")." << std::endl;
        exit(1);
    }

    if (row < 0 || row >= this->data.size()) {
        std::cerr << "Row index (" << std::to_string(row) << ") out of range (0.." << std::to_string(this->data.size()) << ")." << std::endl;
        exit(1);
    }

    return this->data[row][column];
}

void DataTable::setRow(int32_t row, std::vector<int32_t> values){
    if (values.size() != this->columns) {
        std::cerr << "values array size (" << std::to_string(values.size()) << ") must match DataTable nColumns (" << std::to_string(this->columns) << ")." << std::endl;
        exit(1);
    }

    for (int32_t i=0; i<values.size(); i++) {
        this->set(row, i, values[i]);
    }
}

std::vector<int32_t> DataTable::getRow(int32_t row){
    if (row < 0 || row >= this->data.size()) {
        std::cerr << "Row index (" << std::to_string( row) << ") out of range (0.." <<  std::to_string(this->data.size()) << ")." << std::endl;
        exit(1);
    }

    std::vector<int32_t> returnArray = std::vector<int32_t>(this->columns);
    for(int i=0; i<this->columns; i++) {
        returnArray[i] = this->get(row, i);
    }
    return returnArray;
}

void DataTable::addRow(std::vector<int32_t> values){
    if (values.size() != this->columns) {
        std::cerr << "values array size (" << std::to_string( values.size()) << ") must match DataTable nColumns (" << std::to_string( this->columns)  << ")." << std::endl;
        exit(1);
    }

    this->setRow(this->data.size(), values);
}
}
