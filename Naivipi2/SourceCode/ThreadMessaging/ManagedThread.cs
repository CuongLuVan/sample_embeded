using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading;

using ThreadMessaging.Messages;

namespace ThreadMessaging
{
    /// <summary>
    /// Class to wrap a thread under management
    /// </summary>
    internal class ManagedThread : IThread
    {
        /// <summary>
        /// This thread's message queue
        /// </summary>
        private MessageQueue msgQueue;

        /// <summary>
        /// The managed thread's name
        /// </summary>
        private string name;

        /// <summary>
        /// The user's message handler that will be called with messages
        /// </summary>
        private Action<BaseMessage> messageHandler;

        /// <summary>
        /// Wait time in milli seconds to pend for a message before returning
        /// </summary>
        private int waitTimeInMilliseconds = -1;

        /// <summary>
        /// Reference to the main processing loop to use
        /// </summary>
        private Action<object> mainProcessingLoop;

        /// <summary>
        /// Constructor for the infinite wait at the message queue
        /// </summary>
        public ManagedThread(string name, Action<BaseMessage> messageHandler)
        {
            msgQueue = new MessageQueue(name);
            this.name = name;
            this.mainProcessingLoop = mainLoop;
            this.messageHandler = messageHandler;
        }

        /// <summary>
        /// Constructor for the timed wait at the message queue
        /// </summary>
        public ManagedThread(
            string name,
            Action<BaseMessage> messageHandler,
            int waitTimeInMilliseconds)
        {
            msgQueue = new MessageQueue(name);
            this.name = name;
            this.mainProcessingLoop = mainLoop;
            this.messageHandler = messageHandler;
            this.waitTimeInMilliseconds = waitTimeInMilliseconds;
        }

        /// <summary>
        /// Main processing loop for the thread. This one implements both the infinite
        /// and timed wait for new messages.
        /// </summary>
        /// <param name="state"></param>
        private void mainLoop(object state)
        {
            Thread.CurrentThread.Name = name;
            bool run = true;
            while (run == true)
            {
                // Call the appropriate GetMessage() method
                BaseMessage msg = null;
                if (waitTimeInMilliseconds == -1)
                    msg = msgQueue.GetMessage();
                else
                    msg = msgQueue.GetMessage(waitTimeInMilliseconds);

                // If a message returned, check its type
                if (msg != null)
                {
                    switch (msg.MsgType)
                    {
                        // Stop message, clear the flag so we exit the loop
                        // and end the thread
                        case MessageType.StopThread:
                            run = false;
                            break;
                        default:
                            // Call the user's supplied message handler
                            messageHandler(msg);
                            break;
                    }
                }
                else
                    // If we get here the caller has opted for time outs
                    messageHandler(msg);
            }
        }

        #region IThread Implementation
        /// <summary>
        /// The thread name
        /// </summary>
        public string Name { get { return name; } }

        /// <summary>
        /// Start this thread running
        /// </summary>
        public void StartThread()
        {
            ThreadPool.QueueUserWorkItem(new WaitCallback(mainProcessingLoop));
        }

        /// <summary>
        /// Stop this thread
        /// </summary>
        public void StopThread()
        {
            MessageStopThread stop = new MessageStopThread();
            msgQueue.SendMessage(stop);
        }

        /// <summary>
        /// Send a message to this thread
        /// </summary>
        /// <param name="msg"></param>
        public void SendMessage(BaseMessage msg)
        {
            msgQueue.SendMessage(msg);
        }
        #endregion
    }
}
