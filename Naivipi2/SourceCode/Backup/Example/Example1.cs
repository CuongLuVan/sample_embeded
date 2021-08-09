using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

using ThreadMessaging;
using ThreadMessaging.Messages;

namespace Example
{
    /// <summary>
    /// Class to handle the thread messaging loop for Example 1.
    /// This class is used to encapsulate all the objects maintained by the thread.
    /// </summary>
    public class Example1
    {
        /// <summary>
        /// Name of this thread
        /// </summary>
        public readonly string ThreadName;

        /// <summary>
        /// Delegate used to send the message on to the next thread
        /// </summary>
        private Action<BaseMessage> sendMsg;

        /// <summary>
        /// Ctor
        /// </summary>
        /// <param name="threadName"></param>
        /// <param name="sendMsg"></param>
        public Example1(string threadName, Action<BaseMessage> sendMsg)
        {
            ThreadName = threadName;
            this.sendMsg = sendMsg;
        }

        /// <summary>
        /// Received message handler
        /// </summary>
        /// <param name="msg"></param>
        public void MessageHandler(BaseMessage msg)
        {
            switch (msg.MsgType)
            {
                case MessageType.Message1:
                    {
                        Message1 msg1 = (Message1)msg;

                        // Sleep for the requested time
                        System.Threading.Thread.Sleep(msg1.DelayInMilliSeconds);

                        // And then send the message on to the next thread
                        sendMsg(msg1);
                    }
                    break;
            }
        }
    }
}
