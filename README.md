# Critical Path Method Visualizer

The Critical Path Method (CPM) Visualizer is a powerful tool designed to help project managers and teams efficiently manage and visualize project schedules. The CPM technique identifies the longest sequence of dependent activities and determines the minimum time required to complete a project. This README provides an overview of the CPM Visualizer, its features, installation instructions, and usage guidelines.

## Features

- **Interactive Interface**: Intuitive user interface for easy input of activities and their durations.
- **Visualization**: Visual representation of the project schedule, including critical path highlighting.
- **Critical Path Analysis**: Automatic identification of the critical path and its duration.
- **Customizable Output**: Options to customize the visualization to suit specific project needs.
- **Export Functionality**: Ability to export the project schedule and critical path data for further analysis.


### Downloading the Last Release

1. Navigate to the [Releases](https://github.com/Grallistrix/CPM_Visualizer/releases) section of the repository.

2. Download the latest release package

3. Extract the contents of the zip file to your desired location.

4. Run the executable file.

### Compiling from Source (C++ Builder)

1. Clone the repository to your local machine:

    ```bash
    git clone https://github.com/yourusername/critical-path-visualizer.git
    ```

2. Open the project in your preferred C++ 11 builder (e.g., Visual Studio, Xcode, Code::Blocks).

3. Add the files and compile the project to generate the executable file.

4. Run the executable file.

## Usage

1. Run the program
  
3. Input the activities and their durations and predecessors as prompted by the interface.

4. When ready, click the CALC button

5. Review the generated schedule visualization and critical path.

6. (OPTIONAL) CLick your preferred activity and the "INFO" button to view in-depth statistics about the selected activity, including its duration, earliest start and finish times, latest start and finish times, and reserve time.

## Example

Consider a construction project with the following activities:

- Excavation (2 days)
- Foundation (5 days)
- Framing (10 days)
- Roofing (7 days)
- Interior (8 days)
- Finishing (5 days)

By inputting these activities and durations into the CPM Visualizer, you can visualize the project schedule and identify the critical path, which determines the minimum project duration based on activity dependencies.

## License

This project is licensed under the MIT License.

