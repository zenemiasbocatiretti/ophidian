#include "ChipBoundaries.h"

#define VERBOSE 0 //print estimation of cache misses

//using namespace ophidian;
namespace ophidian
{
namespace experiments
{
namespace chip_boundaries
{

PlacementCell::PlacementCell(const std::string & name, const bool fixed, std::size_t pins_size) : Cell(name, pins_size), m_fixed(m_fixed){
}
void PlacementCell::set_geometry(multibox geometry){
    m_geometry = geometry;
}
void PlacementCell::set_position(const util::LocationDbu & position){
    m_position = position;
}
const util::LocationDbu PlacementCell::get_position(){
    return m_position;
}

void chip_boundaries_sequential_ood(design::Design &design, Metric &metric)
{
    using Cell = ophidian::circuit::Cell;

    util::LocationDbu m_chip_Origin = design.floorplan().chipOrigin();
    util::LocationDbu m_chip_UpperRightCorner = design.floorplan().chipUpperRightCorner();

    std::vector<PlacementCell> m_cells;
    m_cells.reserve(design.netlist().size(ophidian::circuit::Cell()));

    for(auto cell_it = design.netlist().begin(Cell()); cell_it != design.netlist().end(Cell()); ++cell_it)
    {
        auto cell = *cell_it;
        PlacementCell p_cell(design.netlist().name(cell), design.placement().isFixed(cell), design.netlist().pins(cell).size());
        p_cell.set_geometry(design.placementMapping().geometry(cell));
        p_cell.set_position(design.placement().cellLocation(cell));
        m_cells.push_back(p_cell);
    }

#if VERBOSE
    std::cout<<"---- INFO: teste miss----"
             <<"\nNumber Objects: "<< design.netlist().size(ophidian::circuit::Cell())
//        << "\nIterations: " << ITERATIONS
             << "\nsize Object : " << sizeof(ophidian::experiments::chip_boundaries::PlacementCell)
//        << "\nsize Vector : " << sizeof(registers)
             << "\n expected cache misses: " << design.netlist().size(ophidian::circuit::Cell()) * sizeof(ophidian::experiments::chip_boundaries::PlacementCell) / 64
             << "\n------" <<std::endl;
#endif

    bool placemente_is_legal = true;

    metric.start();
    for(auto cell_it = m_cells.begin(); cell_it < m_cells.end(); ++cell_it)
    {
        auto cell = *cell_it;
        auto position = cell.get_position();
        if(position.x() < m_chip_Origin.x() || position.y() < m_chip_Origin.y() || position.x() > m_chip_UpperRightCorner.x() || position.y() > m_chip_UpperRightCorner.y())
        {
            placemente_is_legal = false;
        }
    }
    metric.end();
}
void chip_boundaries_parallel_ood(design::Design &design, Metric &metric)
{
    using Cell = ophidian::circuit::Cell;

    util::LocationDbu m_chip_Origin = design.floorplan().chipOrigin();
    util::LocationDbu m_chip_UpperRightCorner = design.floorplan().chipUpperRightCorner();

    std::vector<PlacementCell> m_cells;
    m_cells.reserve(design.netlist().size(ophidian::circuit::Cell()));

    for(auto cell_it = design.netlist().begin(Cell()); cell_it != design.netlist().end(Cell()); ++cell_it)
    {
        auto cell = *cell_it;
        PlacementCell p_cell(design.netlist().name(cell), design.placement().isFixed(cell), design.netlist().pins(cell).size());
        p_cell.set_geometry(design.placementMapping().geometry(cell));
        p_cell.set_position(design.placement().cellLocation(cell));
        m_cells.push_back(p_cell);
    }

#if VERBOSE
    std::cout<<"---- INFO: teste miss----"
             <<"\nNumber Objects: "<< design.netlist().size(ophidian::circuit::Cell())
//        << "\nIterations: " << ITERATIONS
             << "\nsize Object : " << sizeof(ophidian::experiments::chip_boundaries::PlacementCell)
//        << "\nsize Vector : " << sizeof(registers)
             << "\n expected cache misses: " << design.netlist().size(ophidian::circuit::Cell()) * sizeof(ophidian::experiments::chip_boundaries::PlacementCell) / 64
             << "\n------" <<std::endl;
#endif

    bool placemente_is_legal = true;

    metric.start();
#pragma omp parallel for
    for(auto cell_it = m_cells.begin(); cell_it < m_cells.end(); ++cell_it)
    {
        auto cell = *cell_it;
        auto position = cell.get_position();
        if(position.x() < m_chip_Origin.x() || position.y() < m_chip_Origin.y() || position.x() > m_chip_UpperRightCorner.x() || position.y() > m_chip_UpperRightCorner.y())
        {
            placemente_is_legal = false;
        }
    }
    metric.end();
}

void chip_boundaries_sequential_dod(ophidian::design::Design &design, Metric &metric){
    util::LocationDbu m_chip_Origin = design.floorplan().chipOrigin();
    util::LocationDbu m_chip_UpperRightCorner = design.floorplan().chipUpperRightCorner();
    bool placement_is_legal = true;
    auto range = design.placement().cellLocationRange();

#if VERBOSE
    std::cout<<"---- INFO: teste miss----"
             <<"\nNumber Objects: "<< design.netlist().size(ophidian::circuit::Cell())
//        << "\nIterations: " << ITERATIONS
             << "\nsize Object : " << sizeof(ophidian::util::LocationDbu)
//        << "\nsize Vector : " << sizeof(registers)
             << "\n expected cache misses: " << design.netlist().size(ophidian::circuit::Cell()) * sizeof(ophidian::util::LocationDbu) / 64
             << "\n------" <<std::endl;
#endif

    metric.start();
    for(auto position_it = range.begin(); position_it < range.end(); ++position_it)
    {
        auto position = *position_it;
        if(position.x() < m_chip_Origin.x() || position.y() < m_chip_Origin.y() || position.x() > m_chip_UpperRightCorner.x() || position.y() > m_chip_UpperRightCorner.y())
        {
            placement_is_legal = false;
//            break;
        }
    }
    metric.end();
}

void chip_boundaries_parallel_dod(ophidian::design::Design &design, Metric &metric){
    util::LocationDbu m_chip_Origin = design.floorplan().chipOrigin();
    util::LocationDbu m_chip_UpperRightCorner = design.floorplan().chipUpperRightCorner();
    bool placement_is_legal = true;
    auto range = design.placement().cellLocationRange();

#if VERBOSE
    std::cout<<"---- INFO: teste miss----"
             <<"\nNumber Objects: "<< design.netlist().size(ophidian::circuit::Cell())
//        << "\nIterations: " << ITERATIONS
             << "\nsize Object : " << sizeof(ophidian::util::LocationDbu)
//        << "\nsize Vector : " << sizeof(registers)
             << "\n expected cache misses: " << design.netlist().size(ophidian::circuit::Cell()) * sizeof(ophidian::util::LocationDbu) / 64
             << "\n------" <<std::endl;
#endif

    metric.start();
#pragma omp parallel for
    for(auto position_it = range.begin(); position_it < range.end(); ++position_it)
    {
        auto position = *position_it;
        if(position.x() < m_chip_Origin.x() || position.y() < m_chip_Origin.y() || position.x() > m_chip_UpperRightCorner.x() || position.y() > m_chip_UpperRightCorner.y())
        {
            placement_is_legal = false;
//            break;
        }
    }
    metric.end();
}

} // namespace chip_boundaries
} // namespace experiments
} // namespace ophidian