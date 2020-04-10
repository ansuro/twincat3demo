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
                initBsp1();
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
            disposeBsp1();
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
            else
            {
                // unknown notification
                Console.WriteLine("unknown notification handle: " + e.NotificationHandle);
            }

            // update label on UI-Thread
            Dispatcher.Invoke(() => ((Label)e.UserData).Content = result);
        }

        // Beispiel 1 code
        private string bsp1Symbole = "beispiele_Obj1 (ModuleBeispiel1).CppMember";
        AdsStream bsp1ReadStream = new AdsStream(sizeof(UInt32));
        private int bsp1NotificationHandle = 0;

        private void initBsp1()
        {
            // add notification handler
            bsp1NotificationHandle = adsClient.AddDeviceNotification(bsp1Symbole, bsp1ReadStream, AdsTransMode.OnChange, 200, 0, lblMemberUpdate);
        }

        private void disposeBsp1()
        {
            // delete notification handler
            adsClient.DeleteDeviceNotification(bsp1NotificationHandle);
        }

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

    }
}
