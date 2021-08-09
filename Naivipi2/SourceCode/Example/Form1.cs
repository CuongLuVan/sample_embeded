using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Windows.Forms;

using System.IO;

using ThreadMessaging;
using ThreadMessaging.Messages;

namespace Example
{
    /// <summary>
    /// Form to demo the thread messaging library
    /// </summary>
    public partial class Form1 : Form
    {
        /// <summary>
        /// Thread manager interface
        /// </summary>
        private IThreadManager threadMgr;

        /// <summary>
        /// Collection of managed thread interfaces by thread name
        /// </summary>
        private Dictionary<string, IThread> threads;

        #region Example 2 Variables
        /// <summary>
        /// Queues for storing messages from the threads in the same order as they are received
        /// </summary>
        private Queue<int> thread1Queue;
        private Queue<int> thread2Queue;
        private Queue<int> thread3Queue;

        /// <summary>
        /// The number of messages expected from each thread
        /// </summary>
        private int numberOfExpectedMessages;
        #endregion

        public Form1()
        {
            InitializeComponent();
        }

        private void Form1_Load(object sender, EventArgs e)
        {
        }

        #region Example 1 Daisy Chained Message Loop Example
        /// <summary>
        /// Start the daisy chained loop test
        /// </summary>
        /// <param name="sender"></param>
        /// <param name="e"></param>
        private void btnStartSleepLoop_Click(object sender, EventArgs e)
        {
            btnStartSleepLoop.Enabled = false;
            this.Cursor = Cursors.WaitCursor;
            try
            {
                threads = new Dictionary<string, IThread>();
                txtLoopTestDone.Text = "Test running";

                // Get a reference to the thread manager
                threadMgr = ThreadManager.GetThreadManager();

                // Create 3 threads for passing around the sleep message
                // Create them in reverse order as thread 1 needs to know thread 2's mail box, etc.
                Example1 worker3 = new Example1(
                    "Thread3",
                    threadMgr.SendMessage); // Thread 3 sends the message back to this thread
                IThread thread3 = threadMgr.CreateThread(worker3.ThreadName, worker3.MessageHandler);
                threads.Add(worker3.ThreadName, thread3);

                Example1 worker2 = new Example1(
                    "Thread2",
                    thread3.SendMessage); // Thread 2 sends the message to thread 3
                IThread thread2 = threadMgr.CreateThread(worker2.ThreadName, worker2.MessageHandler);
                threads.Add(worker2.ThreadName, thread2);

                Example1 worker1 = new Example1(
                    "Thread1",
                    thread2.SendMessage); // Thread 1 sends the message to thread 2
                IThread thread1 = threadMgr.CreateThread(worker1.ThreadName, worker1.MessageHandler);
                threads.Add(worker1.ThreadName, thread1);

                // Wire in the message received event handler
                threadMgr.ReceivedMessage += new Action<BaseMessage>(threadMgr_NewMessage);

                // Start the threads running
                threadMgr.StartAllThreads();

                // Send a message to the 1st thread
                Message1 msg = new Message1(Convert.ToInt32(txtDelay.Text) * 1000);
                thread1.SendMessage(msg);
            }
            catch (Exception ex)
            {
                this.Cursor = Cursors.Default;
                MessageBox.Show(ex.Message);
                btnStartSleepLoop.Enabled = true;
            }
            finally
            {
                this.Cursor = Cursors.Default;
            }
        }

        /// <summary>
        /// This form has gotten a message, i.e. from thread 3
        /// </summary>
        void threadMgr_NewMessage(BaseMessage msg)
        {
            if (msg != null)
            {
                switch (msg.MsgType)
                {
                    // Thread 3 has finished processing and sent the message on to us
                    case MessageType.Message1:
                        // Clean up
                        threadMgr.ReceivedMessage -= threadMgr_NewMessage;
                        threadMgr.StopAllThreads();
                        threadMgr.ClearAllThreads();
                        threads.Clear();
                        loopTestUpdateForm();
                        break;
                }
            }
        }

        /// <summary>
        /// Update the form for the test complete
        /// </summary>
        private void loopTestUpdateForm()
        {
            if (btnStartSleepLoop.InvokeRequired)
                Invoke(new Action(loopTestUpdateForm)); 
            else
            {
                btnStartSleepLoop.Enabled = true;
                txtLoopTestDone.Text = "Test Complete";
            }
        }

        #endregion

        #region Example 2 Load and Dropped Message Test
        private void btnStart_Click(object sender, EventArgs e)
        {
            btnStart.Enabled = false;
            this.Cursor = Cursors.WaitCursor;
            try
            {
                listBox1.Items.Clear();
                listBox2.Items.Clear();
                listBox3.Items.Clear();
                threads = new Dictionary<string, IThread>();
                thread1Queue = new Queue<int>();
                thread2Queue = new Queue<int>();
                thread3Queue = new Queue<int>();
                txtLoadStatus.Text = "Test running";
                numberOfExpectedMessages = Convert.ToInt32(txtNumberOfMessages.Text);

                // Get a reference to the thread manager
                threadMgr = ThreadManager.GetThreadManager();

                // Create 3 threads for firing a sequence of messages
                Example2 worker = new Example2(
                    "Thread1", 
                    Convert.ToInt32(txtNumberOfMessages.Text), 
                    threadMgr.SendMessage);
                IThread thread1 = threadMgr.CreateThread(worker.ThreadName, worker.MessageHandler);
                threads.Add(worker.ThreadName, thread1);

                worker = new Example2(
                    "Thread2",
                    Convert.ToInt32(txtNumberOfMessages.Text),
                    threadMgr.SendMessage);
                IThread thread2 = threadMgr.CreateThread(worker.ThreadName, worker.MessageHandler);
                threads.Add(worker.ThreadName, thread2);

                worker = new Example2(
                    "Thread3",
                    Convert.ToInt32(txtNumberOfMessages.Text),
                    threadMgr.SendMessage);
                IThread thread3 = threadMgr.CreateThread(worker.ThreadName, worker.MessageHandler);
                threads.Add(worker.ThreadName, thread3);

                // Wire in the message received event handler
                threadMgr.ReceivedMessage += new Action<BaseMessage>(threadMgr_ReceivedMessage);

                // Start the threads running
                threadMgr.StartAllThreads();

                // Send a message to the threads to start
                Message2A msg = new Message2A();
                thread1.SendMessage(msg);
                msg = new Message2A();
                thread2.SendMessage(msg);
                msg = new Message2A();
                thread3.SendMessage(msg);
            }
            catch (Exception ex)
            {
                this.Cursor = Cursors.Default;
                MessageBox.Show(ex.Message);
                btnStart.Enabled = true;
            }
            finally
            {
                this.Cursor = Cursors.Default;
            }
        }

        /// <summary>
        /// We've received a message from one of the 3 worker threads
        /// </summary>
        /// <param name="msg"></param>
        void threadMgr_ReceivedMessage(BaseMessage msg)
        {
            switch (msg.MsgType)
            {
                case MessageType.Message2B:
                    Message2B msg2B = (Message2B)msg;
                    if (msg2B.ThreadName == "Thread1")
                        thread1Queue.Enqueue(msg2B.SequenceNumber);
                    else if (msg2B.ThreadName == "Thread2")
                        thread2Queue.Enqueue(msg2B.SequenceNumber);
                    else if (msg2B.ThreadName == "Thread3")
                        thread3Queue.Enqueue(msg2B.SequenceNumber);

                    if (thread1Queue.Count == numberOfExpectedMessages &&
                        thread2Queue.Count == numberOfExpectedMessages &&
                        thread3Queue.Count == numberOfExpectedMessages)
                    {
                        // Clean up
                        threadMgr.StopAllThreads();
                        threadMgr.ClearAllThreads();
                        threads.Clear();
                        loadTestUpdateForm();
                    }
                    break;
            }
        }

        /// <summary>
        /// Update the form for the test complete
        /// </summary>
        private void loadTestUpdateForm()
        {
            if (btnStart.InvokeRequired)
                Invoke(new Action(loadTestUpdateForm));
            else
            {
                btnStart.Enabled = true;
                txtLoadStatus.Text = "Test Complete";

                CheckMessageSequencing(listBox1, thread1Queue);
                CheckMessageSequencing(listBox2, thread2Queue);
                CheckMessageSequencing(listBox3, thread3Queue);
            }
        }

        /// <summary>
        /// Check that the messages from a thread are all in sequence
        /// </summary>
        /// <param name="listBox"></param>
        /// <param name="msgs"></param>
        private void CheckMessageSequencing(ListBox listBox, Queue<int> msgs)
        {
            string errorMessage = string.Empty;
            int seq = 0;
            while (msgs.Count > 0)
            {
                int msgSeq = msgs.Dequeue();
                if (msgSeq != seq)
                    errorMessage = "Messages out of sequence";
                listBox.Items.Add(msgSeq.ToString());
                seq++;
            }
            if (errorMessage != string.Empty)
                MessageBox.Show(errorMessage);
        }
        #endregion

    }
}
