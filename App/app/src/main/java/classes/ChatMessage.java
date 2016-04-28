package classes;

/**
 * Class that models a chat message
 */
public class ChatMessage {
    private boolean mIsImage;
    private boolean mIsMine;
    private String mContent;

    /**
     * Constructor of the class ChatMessage
     * @param message a message
     * @param mine true if the message is from the user, false if it is from other user
     * @param image true if the message is an image
     */
    public ChatMessage(String message, boolean mine, boolean image) {
        mContent = message;
        mIsMine = mine;
        mIsImage = image;
    }

    /**
     * Returns the content of the message
     * @return a string that is the content of the message
     */
    public String getContent() {
        return mContent;
    }

    /**
     * Sets the content of the message
     * @param content the string that is the message to be sent
     */
    public void setContent(String content) {
        this.mContent = content;
    }

    /**
     * Returns true if the message is from the user
     * @return true if the message is from the user
     */
    public boolean isMine() {
        return mIsMine;
    }

    /**
     * Sets that the message is or not from the user
     * @param isMine true if the message is from the user
     */
    public void setIsMine(boolean isMine) {
        this.mIsMine = isMine;
    }

    /**
     * Returns true if the message is an image
     * @return true is the message is an image
     */
    public boolean ismIsImage() {
        return mIsImage;
    }

    /**
     * Set that the message is or not an image
     * @param isImage true if the message is an image
     */
    public void setIsImage(boolean isImage) {
        this.mIsImage = isImage;
    }
}
