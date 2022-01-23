from django.shortcuts import render, HttpResponse, get_object_or_404, HttpResponseRedirect, Http404, reverse
from trainer.models import Trainer
from .models import Message
from django.contrib.auth.models import User
from .forms import MessageForm, MessagetoTrainerForm
from django.core.mail import send_mail
from django.conf import settings

def message_view(request):

    if not request.user.is_authenticated:
        return Http404()

    form = MessageForm(request.POST or None)
    if form.is_valid():
        message = form.save(commit=False)
        message.sender = request.user
        message.save()
        return HttpResponseRedirect(reverse('messaging:index'))

    messages = Message.objects.all()
    received_messages = None
    sent_messages = None
    if request.user.is_authenticated:
        received_messages = messages.filter(receiver=request.user)
        sent_messages = messages.filter(sender=request.user)

    context = {
        'received_messages': received_messages,
        'sent_messages': sent_messages,
        'form': form,
    }

    return render(request, 'messaging/messages.html', context)

def send_message_to_trainer(request, trainer_id):

    if not request.user.is_authenticated:
        return Http404()

    trainer = get_object_or_404(Trainer, id=trainer_id)
    receiver = get_object_or_404(User, id=trainer.User_ID.id)
    form = MessagetoTrainerForm(request.POST or None)

    if form.is_valid():
        message = form.save(commit=False)
        message.sender = request.user
        message.receiver = receiver
        message.save()
        return HttpResponseRedirect(reverse('messaging:index'))

    return render(request, 'messaging/form.html', {'form': form})

def trainer_update(request, id):
    if not request.user.is_authenticated:
        return Http404()

    trainer = get_object_or_404(Trainer, id=id)
    print(trainer.User_ID)
    form = TrainerForm(request.POST or None, request.FILES or None, instance=trainer)
    if form.is_valid():
        if request.user == trainer.User_ID:
            form.save()
            messages.success(request, 'Successfully updated!')
            return HttpResponseRedirect(trainer.get_absolute_url())
        else:
            messages.warning(request, 'You can not edit another trainer\'s information.')
            return redirect('trainer:index')
    context = {
        'form': form,
    }
    return render(request, 'trainer/form.html', context)

# Create your views here.
def message_view2(request):
    # Kullaniciya ait olan mesajlarin listelenmesi

    messages = Message.objects.all()
    received_messages = None
    sent_messages = None
    if request.user.is_authenticated:
        received_messages = messages.filter(receiver=request.user)
        sent_messages = messages.filter(sender=request.user)

    return render(request, 'messaging/messages2.html', {'received_messages': received_messages, 'sent_messages': sent_messages})

def create_message(request):
    if not request.user.is_authenticated:
        return Http404()

    form = MessageForm(request.POST or None)
    if form.is_valid():
        message = form.save(commit=False)
        message.sender = request.user
        message.save()
        return HttpResponseRedirect(reverse('messaging:index'))

    context = {
        'form': form,
    }

    return render(request, 'messaging/form.html', context)
