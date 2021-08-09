using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading;

using ThreadMessaging.Messages;

namespace ThreadMessaging
{
    /// <summary>
    /// Implements a message queue for a thread.
    /// </summary>
    internal class MessageQueue
    {
        /// <summary>
        /// Queue for FIFO processing of messages
        /// </summary>
        private Queue<BaseMessage> msgQueue;

        /// <summary>
        /// Event signalling to the thread that a message has arrived
        /// </summary>
        private ManualResetEvent messageArrivedEvent;

        /// <summary>
        /// Mutual exclusion of threads to proteced resources
        /// </summary>
        private object mutexObject;

        /// <summary>
        /// Name of the managed threead that owns this message queue
        /// </summary>
        private readonly string threadName;

        /// <summary>
        /// Constructor
        /// </summary>
        public MessageQueue(string threadName)
        {
            msgQueue = new Queue<BaseMessage>();
            messageArrivedEvent = new ManualResetEvent(false);
            mutexObject = new object();
            this.threadName = threadName;
        }

        /// <summary>
        /// Send a message to the thread that owns this message queue
        /// </summary>
        /// <param name="msg"></param>
        public void SendMessage(BaseMessage msg)
        {
            lock(mutexObject)
            {
                msgQueue.Enqueue(msg);
                messageArrivedEvent.Set();
            }
        }

        /// <summary>
        /// Get a message. If no messages wait indefinitely for one.
        /// </summary>
        /// <returns></returns>
        public BaseMessage GetMessage()
        {
            BaseMessage msg = null;

            // Only wait for a signal if no messages present
            if(msgQueue.Count == 0)
                messageArrivedEvent.WaitOne();
            lock (mutexObject)
            {
                msg = msgQueue.Dequeue();
                messageArrivedEvent.Reset();
            }

            return msg;
        }

        /// <summary>
        /// Get a message. Only wait for the time out period before returning, null return value indicates
        /// no messages were received.
        /// </summary>
        /// <param name="waitTime"></param>
        /// <returns></returns>
        public BaseMessage GetMessage(int waitTime)
        {
            BaseMessage msg = null;

            // Don't wait for a signal if a message present
            if (msgQueue.Count > 0 || messageArrivedEvent.WaitOne(waitTime) == true)
            {
                lock (mutexObject)
                {
                    msg = msgQueue.Dequeue();
                    messageArrivedEvent.Reset();
                }
            }
            return msg;
        }
    }
}
