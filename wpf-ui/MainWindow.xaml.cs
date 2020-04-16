using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows;
using System.Windows.Controls;
using System.Windows.Data;
using System.Windows.Documents;
using System.Windows.Input;
using System.Windows.Media;
using System.Windows.Media.Imaging;
using System.Windows.Navigation;
using System.Windows.Shapes;
using TwinCAT;
using TwinCAT.Ads;

namespace wpf_ui
{
    /// <summary>
    /// Interaktionslogik für MainWindow.xaml
    /// </summary>
    public partial class MainWindow : Window
    {
        // ads connection-specific code

        private TcAdsClient adsClient = new TcAdsClient();
        private const int port = 350;

        public MainWindow()
        {
            InitializeComponent();
            adsClient.ConnectionStateChanged += AdsClient_ConnectionStateChanged;
            adsClient.AdsNotification += AdsClient_NotificationHandler;
        }

        private void AdsClient_ConnectionStateChanged(object sender, TwinCAT.ConnectionStateChangedEventArgs e)
        {
            if(e.NewState.Equals(ConnectionState.Connected))
            {
                tabPanel.IsEnabled = true;
                btnConnect.IsEnabled = false;
                InitBeispiele();
            }
            else
            {
                tabPanel.IsEnabled = false;
                btnConnect.IsEnabled = true;
            }
        }

        private void BtnConnect_Click(object sender, RoutedEventArgs e) => adsClient.Connect(port);

        private void Window_Closed(object sender, EventArgs e)
        {
            DisposeBeispiele();
            adsClient.Disconnect();
            adsClient.Dispose();
        }

        // Notification handler for all ADS notifications
        private void AdsClient_NotificationHandler(object sender, AdsNotificationEventArgs e)
        {
            int offset = (int)e.DataStream.Position;
            int length = (int)e.DataStream.Length;

            e.DataStream.Position = offset;
            AdsBinaryReader reader = new AdsBinaryReader(e.DataStream);
            string result = "";

            // handle example-specific notifications
            if(e.NotificationHandle.Equals(bsp1NotificationHandle))
            {
                // example 1 notification
                result = reader.ReadUInt32().ToString();
            }
            else if (e.NotificationHandle.Equals(bsp2NotificationHandle) || e.NotificationHandle.Equals(bsp3NotificationHandle))
            {
                // example 2 notification
                UInt32 id = reader.ReadUInt32();
                UInt32 value = reader.ReadUInt32();
                result = "id: " + id + " value: " + value;
            }
            else if (e.NotificationHandle.Equals(bsp4NotificationHandle1))
            {
                byte b = reader.ReadByte();
                //Console.WriteLine(b);
                result = b.ToString();
            }
            else
            {
                // unknown notification
                Console.WriteLine("unknown notification handle: " + e.NotificationHandle);
            }

            // update label on UI-Thread
            Dispatcher.Invoke(() => ((Label)e.UserData).Content = result);
        }


        private void InitBeispiele()
        {
            // add notification handler
            bsp1NotificationHandle = adsClient.AddDeviceNotification(bsp1Symbole, bsp1ReadStream, AdsTransMode.OnChange, 200, 0, lblMemberUpdate);
            bsp2NotificationHandle = adsClient.AddDeviceNotification(bsp2Symbole, bsp2ReadStream, AdsTransMode.OnChange, 200, 0, lblDataUpdate);
            bsp3NotificationHandle = adsClient.AddDeviceNotification(bsp3Symbole, bsp3ReadStream, AdsTransMode.OnChange, 200, 0, lblServiceUpdate);
            bsp4NotificationHandle1 = adsClient.AddDeviceNotification(bsp4SymboleIO, bsp4ReadStream1, AdsTransMode.OnChange, 200, 0, lblPLCIOUpdate);
        }

        private void DisposeBeispiele()
        {
            // delete notification handler
            adsClient.DeleteDeviceNotification(bsp1NotificationHandle);
            adsClient.DeleteDeviceNotification(bsp2NotificationHandle);
            adsClient.DeleteDeviceNotification(bsp3NotificationHandle);
            adsClient.DeleteDeviceNotification(bsp4NotificationHandle1);
        }

        // Beispiel 1 code
        private string bsp1Symbole = "beispiele_Obj1 (ModuleBeispiel1).CppMember";
        private AdsStream bsp1ReadStream = new AdsStream(sizeof(UInt32));
        private int bsp1NotificationHandle = 0;

        private void BtnMemberRead_Click(object sender, RoutedEventArgs e)
        {
            uint cppMember = (uint) adsClient.ReadSymbol(bsp1Symbole, typeof(UInt32), false);
            txtMember.Text = cppMember.ToString();
        }

        private void BtnMemberWrite_Click(object sender, RoutedEventArgs e)
        {
            string val = txtMember.Text;
            uint w;
            if(UInt32.TryParse(val, out w))
            {
                adsClient.WriteSymbol(bsp1Symbole, w, false);
            }
            else
            {
                MessageBox.Show("Not a number");
            }
        }


        // Beispiel 2 code
        private string bsp2Symbole = "beispiele_Obj3 (ModuleBeispiel2In).Members.Fancy";
        private AdsStream bsp2ReadStream = new AdsStream(sizeof(UInt32) * 2);
        private int bsp2NotificationHandle = 0;

        // Beispiel 3 code
        private string bsp3Symbole = "beispiele_Obj4 (ModuleBeispiel3Consumer).Data.FancyData";
        private AdsStream bsp3ReadStream = new AdsStream(sizeof(UInt32) * 2);
        private int bsp3NotificationHandle = 0;

        private string bsp4SymboleIO = "beispiele_Obj6 (ModuleBeispiel4PlcIoAdsCommunication).Inputs.PLCX";
        private AdsStream bsp4ReadStream1 = new AdsStream(sizeof(Byte));
        private int bsp4NotificationHandle1 = 0;
    }
}
