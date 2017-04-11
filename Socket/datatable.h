
#include <stdlib.h>
#include <iostream>
#include <vector>
#include <sstream>

#ifndef DATATABLE_H_
#define DATATABLE_H_


namespace client{
class DataTable {
public:
    /**
     * Construct a DataTable
     *
     * @param nColumns
     *            the number of columns in this table
     */
    DataTable(int32_t nColumns);
    virtual ~DataTable();



    /**
     * Gets the number of columns in this table
     * @return number of columns
     */
    int32_t getNColumns();

    /**
     * Gets the nuber of rows in this table
     * @return number of rows
     */
    int32_t getNRows();


    /**
     * Set a table cell to a value. If the row does not exist, it is created and
     * initialized to all 0's.
     *
     * @param row Row index, starting at 0
     * @param column Column index, starting at 0
     * @param value
     */
    void set(int32_t row, int32_t column, int32_t value);

    /**
     * Gets a value from the table
     * @param row Row index, starting at 0
     * @param column Column index, starting at 0
     * @return value
     */
    int32_t get(int32_t row, int32_t column);

    /**
     * Inserts a row into the DataTable
     * @param row Row index, starting at 0
     * @param values Integer array of values
     */
    void setRow(int32_t row, std::vector<int32_t> values);

    /**
     * Retrieves a row from the DataTable
     * @param row Row index, starting at 0
     * @return Integer array of valus
     */
    std::vector<int32_t> getRow(int32_t row);

    /**
     * Adds a row to the end of the DataTable
     * @param values Integer array of values
     */
    void addRow(std::vector<int32_t> values);

private:
    std::vector<std::vector<int32_t>> data = std::vector<std::vector<int32_t>>();
    int32_t columns;
};
}
#endif /* DATATABLE_H_ */
