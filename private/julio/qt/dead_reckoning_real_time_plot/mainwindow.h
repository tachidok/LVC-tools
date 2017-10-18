#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QVector>
#include <QString>
#include <QStringList>
#include <QTimer>
#include <QDebug>
#include <QThread>

// To plot
#include "../../../../external_src/qcustomplot/qcustomplot/qcustomplot.h"

// The thread in charge of reading data from ethernet/serial communication
#include "cc_read_data_thread.h"

#define N_DATA_PER_SECOND 10
#define N_SECONDS_IN_HISTORY 10

#define TIMER_TIMEOUT_MS 1000

#define MAX_RAW_GYRO 15.0
#define MIN_RAW_GYRO -15.0
#define MAX_RAW_ACC 9.81*1.5
#define MIN_RAW_ACC -(9.81*1.5)
#define MAX_EULER_ANGLE 180.0
#define MIN_EULER_ANGLE -180.0
#define MAX_VELOCITY 200.0
#define MIN_VELOCITY -200.0
#define MAX_POSITION 10000.0 // In meters
#define MIN_POSITION -10000.0 // In meters

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

    // In charge of filling data into the data structures
    void fill_data(const double time_raw_gyro,
                   const double raw_gyro_x,
                   const double raw_gyro_y,
                   const double raw_gyro_z,
                   const double time_raw_acc,
                   const double raw_acc_x,
                   const double raw_acc_y,
                   const double raw_acc_z,
                   const double time_rotated_gyro,
                   const double rotated_gyro_x,
                   const double rotated_gyro_y,
                   const double rotated_gyro_z,
                   const double time_rotated_acc,
                   const double rotated_acc_x,
                   const double rotated_acc_y,
                   const double rotated_acc_z,
                   const double time_filtered_gyro,
                   const double filtered_gyro_x,
                   const double filtered_gyro_y,
                   const double filtered_gyro_z,
                   const double time_filtered_acc,
                   const double filtered_acc_x,
                   const double filtered_acc_y,
                   const double filtered_acc_z,
                   const double time_aligned_gyro,
                   const double aligned_gyro_x,
                   const double aligned_gyro_y,
                   const double aligned_gyro_z,
                   const double time_aligned_acc,
                   const double aligned_acc_x,
                   const double aligned_acc_y,
                   const double aligned_acc_z,
                   const double time_euler_angle_gyro,
                   const double euler_angle_phi_gyro,
                   const double euler_angle_theta_gyro,
                   const double euler_angle_psi_gyro,
                   const double time_euler_angle_acc,
                   const double euler_angle_phi_acc,
                   const double euler_angle_theta_acc,
                   const double time_euler_angle_fused,
                   const double euler_angle_phi_fused,
                   const double euler_angle_theta_fused,
                   const double euler_angle_psi_fused,
                   const double time_gravity_body_frame,
                   const double gravity_x_body_frame,
                   const double gravity_y_body_frame,
                   const double gravity_z_body_frame,
                   const double time_linear_acc,
                   const double linear_acc_x,
                   const double linear_acc_y,
                   const double linear_acc_z,
                   const double time_inertial_acc,
                   const double inertial_acc_x,
                   const double inertial_acc_y,
                   const double inertial_acc_z,
                   const double time_velocity_body,
                   const double velocity_x,
                   const double velocity_y,
                   const double time_velocity_inertial,
                   const double velocity_north,
                   const double velocity_east,
                   const double time_position_body,
                   const double position_x_body_frame,
                   const double position_y_body_frame,
                   const double time_position_inertial,
                   const double position_x_inertial_frame,
                   const double position_y_inertial_frame);

    // ------------------------------------------------------
    // Data structures to store the computed values
    QVector<double> Time_raw_gyro;
    QVector<double> Raw_gyro_x;
    QVector<double> Raw_gyro_y;
    QVector<double> Raw_gyro_z;
    QVector<double> Time_raw_acc;
    QVector<double> Raw_acc_x;
    QVector<double> Raw_acc_y;
    QVector<double> Raw_acc_z;
    QVector<double> Time_rotated_gyro;
    QVector<double> Rotated_gyro_x;
    QVector<double> Rotated_gyro_y;
    QVector<double> Rotated_gyro_z;
    QVector<double> Time_rotated_acc;
    QVector<double> Rotated_acc_x;
    QVector<double> Rotated_acc_y;
    QVector<double> Rotated_acc_z;
    QVector<double> Time_filtered_gyro;
    QVector<double> Filtered_gyro_x;
    QVector<double> Filtered_gyro_y;
    QVector<double> Filtered_gyro_z;
    QVector<double> Time_filtered_acc;
    QVector<double> Filtered_acc_x;
    QVector<double> Filtered_acc_y;
    QVector<double> Filtered_acc_z;
    QVector<double> Time_aligned_gyro;
    QVector<double> Aligned_gyro_x;
    QVector<double> Aligned_gyro_y;
    QVector<double> Aligned_gyro_z;
    QVector<double> Time_aligned_acc;
    QVector<double> Aligned_acc_x;
    QVector<double> Aligned_acc_y;
    QVector<double> Aligned_acc_z;
    QVector<double> Time_euler_angle_gyro;
    QVector<double> Euler_angle_phi_gyro;
    QVector<double> Euler_angle_theta_gyro;
    QVector<double> Euler_angle_psi_gyro;
    QVector<double> Time_euler_angle_acc;
    QVector<double> Euler_angle_phi_acc;
    QVector<double> Euler_angle_theta_acc;
    QVector<double> Time_euler_angle_fused;
    QVector<double> Euler_angle_phi_fused;
    QVector<double> Euler_angle_theta_fused;
    QVector<double> Euler_angle_psi_fused;
    QVector<double> Time_gravity_body_frame;
    QVector<double> Gravity_x_body_frame;
    QVector<double> Gravity_y_body_frame;
    QVector<double> Gravity_z_body_frame;
    QVector<double> Time_linear_acc;
    QVector<double> Linear_acc_x;
    QVector<double> Linear_acc_y;
    QVector<double> Linear_acc_z;
    QVector<double> Time_inertial_acc;
    QVector<double> Inertial_acc_x;
    QVector<double> Inertial_acc_y;
    QVector<double> Inertial_acc_z;
    QVector<double> Time_velocity_body;
    QVector<double> Velocity_x;
    QVector<double> Velocity_y;
    QVector<double> Time_velocity_inertial;
    QVector<double> Velocity_north;
    QVector<double> Velocity_east;
    QVector<double> Time_position_body;
    QVector<double> Position_x_body_frame;
    QVector<double> Position_y_body_frame;
    QVector<double> Time_position_inertial;
    QVector<double> Position_x_inertial_frame;
    QVector<double> Position_y_inertial_frame;

public slots:

    // Method in charge of calling the corresponing plotting functions
    // based on the combo box selection
    void slot_plot();

private:

    Ui::MainWindow *ui;

    // ------------------------------------------------------
    // List of plots for each widget
    QStringList Plots_options;

    // A vector to store pointers to functions in charge of plotting
    QVector<void (*)(MainWindow *mw, QCustomPlot *wdg_plot)> Plot_function_pt;

    // ----------------------------------------------------------
    // Store as many data as required to keep n seconds in history
    // data N_SECONDS_IN_HISTORY
    int N_data_in_history;

    // The timer in charge of calling the plot functions
    QTimer *Plot_timer;

    // The thread that is used to read data from external application
    QThread Original_read_data_thread;

    // In charge of reading data from an external application via
    // serial/ethernet communication
    cc_read_data_thread Read_data_thread;

};

// --------------------------------------------------------------
// Plot methods (each widget calls one of these to plot its data)
// --------------------------------------------------------------
void plot_raw_gyro_x(MainWindow *mw, QCustomPlot *wdg_plot);
void plot_raw_gyro_y(MainWindow *mw, QCustomPlot *wdg_plot);
void plot_raw_gyro_z(MainWindow *mw, QCustomPlot *wdg_plot);
void plot_raw_acc_x(MainWindow *mw, QCustomPlot *wdg_plot);
void plot_raw_acc_y(MainWindow *mw, QCustomPlot *wdg_plot);
void plot_raw_acc_z(MainWindow *mw, QCustomPlot *wdg_plot);
void plot_rotated_gyro_x(MainWindow *mw, QCustomPlot *wdg_plot);
void plot_rotated_gyro_y(MainWindow *mw, QCustomPlot *wdg_plot);
void plot_rotated_gyro_z(MainWindow *mw, QCustomPlot *wdg_plot);
void plot_rotated_acc_x(MainWindow *mw, QCustomPlot *wdg_plot);
void plot_rotated_acc_y(MainWindow *mw, QCustomPlot *wdg_plot);
void plot_rotated_acc_z(MainWindow *mw, QCustomPlot *wdg_plot);
void plot_filtered_gyro_x(MainWindow *mw, QCustomPlot *wdg_plot);
void plot_filtered_gyro_y(MainWindow *mw, QCustomPlot *wdg_plot);
void plot_filtered_gyro_z(MainWindow *mw, QCustomPlot *wdg_plot);
void plot_filtered_acc_x(MainWindow *mw, QCustomPlot *wdg_plot);
void plot_filtered_acc_y(MainWindow *mw, QCustomPlot *wdg_plot);
void plot_filtered_acc_z(MainWindow *mw, QCustomPlot *wdg_plot);
void plot_aligned_gyro_x(MainWindow *mw, QCustomPlot *wdg_plot);
void plot_aligned_gyro_y(MainWindow *mw, QCustomPlot *wdg_plot);
void plot_aligned_gyro_z(MainWindow *mw, QCustomPlot *wdg_plot);
void plot_aligned_acc_x(MainWindow *mw, QCustomPlot *wdg_plot);
void plot_aligned_acc_y(MainWindow *mw, QCustomPlot *wdg_plot);
void plot_aligned_acc_z(MainWindow *mw, QCustomPlot *wdg_plot);
void plot_euler_angle_phi_gyro(MainWindow *mw, QCustomPlot *wdg_plot);
void plot_euler_angle_theta_gyro(MainWindow *mw, QCustomPlot *wdg_plot);
void plot_euler_angle_psi_gyro(MainWindow *mw, QCustomPlot *wdg_plot);
void plot_euler_angle_phi_acc(MainWindow *mw, QCustomPlot *wdg_plot);
void plot_euler_angle_theta_acc(MainWindow *mw, QCustomPlot *wdg_plot);
void plot_euler_angle_phi_fused(MainWindow *mw, QCustomPlot *wdg_plot);
void plot_euler_angle_theta_fused(MainWindow *mw, QCustomPlot *wdg_plot);
void plot_euler_angle_psi_fused(MainWindow *mw, QCustomPlot *wdg_plot);
void plot_gravity_x_body_frame(MainWindow *mw, QCustomPlot *wdg_plot);
void plot_gravity_y_body_frame(MainWindow *mw, QCustomPlot *wdg_plot);
void plot_gravity_z_body_frame(MainWindow *mw, QCustomPlot *wdg_plot);
void plot_linear_acc_x(MainWindow *mw, QCustomPlot *wdg_plot);
void plot_linear_acc_y(MainWindow *mw, QCustomPlot *wdg_plot);
void plot_linear_acc_z(MainWindow *mw, QCustomPlot *wdg_plot);
void plot_inertial_acc_x(MainWindow *mw, QCustomPlot *wdg_plot);
void plot_inertial_acc_y(MainWindow *mw, QCustomPlot *wdg_plot);
void plot_inertial_acc_z(MainWindow *mw, QCustomPlot *wdg_plot);
void plot_velocity_x(MainWindow *mw, QCustomPlot *wdg_plot);
void plot_velocity_y(MainWindow *mw, QCustomPlot *wdg_plot);
void plot_velocity_north(MainWindow *mw, QCustomPlot *wdg_plot);
void plot_velocity_east(MainWindow *mw, QCustomPlot *wdg_plot);
void plot_position_body_frame(MainWindow *mw, QCustomPlot *wdg_plot);
void plot_position_inertial_frame(MainWindow *mw, QCustomPlot *wdg_plot);
// --------------------------------------------------------------
// --------------------------------------------------------------

#endif // MAINWINDOW_H
