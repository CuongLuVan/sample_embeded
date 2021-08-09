using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

using ThreadMessaging;
using ThreadMessaging.Messages;

namespace Example
{
    /// <summary>
    /// Class to handle Example 2, the load/stress and dropped message test
    /// This class is used to encapsulate all the objects maintained by the thread.
    /// </summary>
    public class Example2
    {
        /// <summary>
        /// Thread name
        /// </summary>
        public readonly string ThreadName;

        /// <summary>
        /// Ascending sequence number sent out in successive messages
        /// </summary>
        private int messageSequenceNumber;

        /// <summary>
        /// The number of messages to send
        /// </summary>
        private int numberOfMessagesToSend;

        /// <summary>
        /// Delegate used to send the sequence of messages back to the thread running the test
        /// </summary>
        private Action<BaseMessage> sendMsg;

        /// <summary>
        /// Ctor
        /// </summary>
        /// <param name="threadName"></param>
        /// <param name="numberOfMessagesToSend"></param>
        /// <param name="sendMsg"></param>
        public Example2(string threadName, int numberOfMessagesToSend, Action<BaseMessage> sendMsg)
        {
            ThreadName = threadName;
            messageSequenceNumber = 0;
            this.numberOfMessagesToSend = numberOfMessagesToSend;
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
                case MessageType.Message2A:
                {
                    // Drop into a loop sending out all the requested messages back to back
                    while (messageSequenceNumber < numberOfMessagesToSend)
                    {
                        Message2B outboundMsg = new Message2B(messageSequenceNumber, ThreadName);
                        sendMsg(outboundMsg);
                        messageSequenceNumber++;
                    }
                }
                break;
            }
        }
    }
}
